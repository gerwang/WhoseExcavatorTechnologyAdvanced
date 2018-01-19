//
// Created by Gerwa on 2017/12/11.
//

#include "Solver.h"
#include <iostream>
#include <fstream>
#include "Test.h"
#include "CSVHandler.h"
#include "Crawler.h"
#include "HttpRequest.h"
#include "HTMLParser.h"
#include "ThreadPool.h"
#include "StringConvert.h"
#include "Logger.h"

std::mutex output_mutex;

void Solver::work(const String& url, ArrayList<String>& result, int urlID) {
	{
		std::unique_lock<std::mutex> lock(output_mutex);
		std::cout << "Starting " << urlID << std::endl;
	}
	result.clear();
	result.push_back(String::number(urlID));
	result.push_back(url);
	result += Crawler().crawl(url, urlID);
	LinkedList<String> titleWords, contentWords;
	if (result.size() == 9) {
		titleWords = wordDivider.divideWords(result[4]);
		contentWords = wordDivider.divideWords(result[5]);
		String res;
		for (auto& word : titleWords) {
			res += word;
			res += " ";
		}
		for (auto& word : contentWords) {
			res += word;
			res += " ";
		}
		result.push_back(res);
	}
	{
		std::unique_lock<std::mutex> lock(output_mutex);
		for (auto& word : titleWords) {
			auto& dc = treeMap[word];
			dc.addTime(urlID, 1);
		}
		for (auto& word : contentWords) {
			auto& dc = treeMap[word];
			dc.addTime(urlID, 1);
		}
		std::cout << "Complete " << urlID << std::endl;
	}
}

void Solver::loadPages() {
	HttpRequest::startUp();
	wordDivider.loadDict("dictionary.dic");
	wordDivider.loadDict("term.dic");
	wordDivider.loadDict("query.txt");///<@note 将查询词作为词典插入
	wordDivider.loadStopWords("stopword.dic");
	handler.load("input/url.csv");
	auto& csv = handler.getCSV();
	auto& csvout = output.getCSV();
	csvout.resize(csv.size());
	csvout[0].push_back(L"序号");
	csvout[0].push_back(L"网址");
	csvout[0].push_back(L"发帖大类");
	csvout[0].push_back(L"发帖小类");
	csvout[0].push_back(L"发帖标题");
	csvout[0].push_back(L"发帖内容");
	csvout[0].push_back(L"发帖人");
	csvout[0].push_back(L"发帖日期");
	csvout[0].push_back(L"发帖类型");
	csvout[0].push_back(L"分词结果");
	/*!
	 * @note single thread code
	 *
	for (int row = 1; row < csv.size(); row++) {
		const String &url = csv[row][1];
		ArrayList<String> holder;
		work(url, holder, wordDivider, row);
		csvout.push_back(std::move(holder));
//        std::cout << "Complete " << row << std::endl;
	}
	*/
	///<@note 为了多线程，一定要先开好
	{
		ThreadPool pool(50);
		for (int row = 1; row < csv.size(); row++) {
			const String& url = csv[row][1];
			ArrayList<String>& backPtr = csvout[row];
			pool.addTask([this, url, &backPtr, row]() {
				work(url, backPtr, row);
			});
		}
	}
	output.save("input/result.csv");
	HttpRequest::tearDown();
}

ArrayList<DocNode> Solver::searchQuery(const String& queryLine) {

	ArrayList<String> querys;
	{
		int index = 0;
		while (index < queryLine.length()) {
			index = HTMLParser::nextNotSpace(queryLine, index);
			int end_index = index;
			while (end_index < queryLine.length() && !iswspace(static_cast<wint_t>(queryLine[end_index]))) {
				end_index++;
			}
			if (index < end_index) {
				querys.push_back(queryLine.substr(static_cast<unsigned int>(index),
					static_cast<unsigned int>(end_index)));
			}
			index = end_index + 1;
		}
	}

	{
		std::sort(querys.begin(), querys.end());
		auto m = std::unique(querys.begin(), querys.end()) - querys.begin();///<@note 去重
		while (querys.size() > m) {
			querys.pop_back();
		}
	}

	struct sort_node {
		int urlID, occurSum, occurTypes;

		sort_node() {
		}

		sort_node(int _urlID, int _occurSum, int _occurTypes) :
			urlID(_urlID), occurSum(_occurSum), occurTypes(_occurTypes) {
		}

		bool operator<(const sort_node& other) const {
			//			if (occurTypes != other.occurTypes) {
			//				return occurTypes > other.occurTypes;
			//			}
			if (occurSum != other.occurSum) {
				return occurSum > other.occurSum;
			}
			return urlID < other.urlID;
		}
	};
	ArrayList<sort_node> sort_nodes;
	ArrayList<int> vis_flags;
	int max_t = 0;
	AvlMap<int, int> idMap;
	auto getID = [&idMap, &sort_nodes, &vis_flags](int urlID) {
		int& val = idMap[urlID];
		if (val == 0) {
			sort_nodes.push_back(sort_node(urlID, 0, 0));
			vis_flags.push_back(0);
			val = sort_nodes.size();
		}
		return val - 1;
	};

	for (auto& word : querys) {
		if (treeMap.count(word) == 0) {
			continue;
		}
		auto& docs = treeMap[word].docs;
		max_t++;
		for (auto& node : docs) {
			int idx = getID(node.urlID);
			if (vis_flags[idx] != max_t) {
				vis_flags[idx] = max_t;
				sort_nodes[idx].occurTypes++;
			}
			sort_nodes[idx].occurSum++;
		}
	}
	std::sort(sort_nodes.begin(), sort_nodes.end());
	ArrayList<DocNode> res;
	for (auto& node : sort_nodes) {
		res.push_back(DocNode(node.urlID, node.occurSum));
	}
	return res;
}

void Solver::solveConsole() {
	std::ifstream fin("query.txt");
	std::ofstream fout("result.txt");
	std::string line;
	while (std::getline(fin, line)) {
		if (!line.empty()) {
			const auto& res = searchQuery(StringConvert::fromStdString(line));///<@note 这里的编码和输入的query.txt有关
			for (const auto& x : res) {
				fout << "(" << x.urlID << "," << x.occurTime << ")" << " ";
			}
			fout << std::endl;
		}
	}
}

void Solver::outputDebug() {
	treeMap.traverse([](const AvlNode<String, DocCounter>* o) {
		String line = o->key + ":[";
		for (auto& node : o->value.docs) {
			line += "(" + String::number(node.urlID) + "," + String::number(node.occurTime) + "), ";
		}
		line += "]";
		Logger::slog(line);
	});
}

CSVHandler& Solver::getOutput() {
	return output;
}

LinkedList<String> Solver::divideLine(String line) {
	return wordDivider.divideWords(line);
}
