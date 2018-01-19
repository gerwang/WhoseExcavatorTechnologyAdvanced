//
// Created by Gerwa on 2017/12/11.
//

#ifdef _WIN32
#define DllExport __declspec(dllexport)
#else
#define DllExport
#endif

#include "Solver.h"
#include "StringConvert.h"
#include "Logger.h"

template<typename CharT>
BasicString<CharT> json_escape(const BasicString<CharT>& str) {
	BasicString<CharT> res;
	res.reserve(str.length());
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '\n') {
			res += R"(\n)";
		}
		else if (str[i] == '\t') {
			res += R"(\t)";
		}
		else if (str[i] == '\\') {
			res += R"(\\)";
		}
		else if (str[i] == '"') {
			res += R"(\")";
		}
		else {
			res.push_back(str[i]);
		}
	}
	return res;
}

extern "C" {
	DllExport Solver *create() {
		return new Solver;
	}

	DllExport void destroy(Solver *app) {
		delete app;
	}

	DllExport const char *get_str(const char *str) {
		return str;
	}

	DllExport void free_str(const char *str) {
		delete[] str;
	}

	DllExport const char *load(Solver *app) {
		app->loadPages();
		std::string cvt_result = "{}";
		auto res = new char[cvt_result.length() + 1];
		strcpy(res, cvt_result.c_str());
		return res;
	}

	DllExport const char *query(Solver *app, const char *line) {
		std::string inputLine(line);
		const String queryLine = StringConvert::fromStdString(inputLine, CP_UTF8);
		const auto &list = app->searchQuery(queryLine);
		String result = "[";
		bool first = true;
		for (const auto &node : list) {
			if (first) {
				first = false;
			}
			else {
				result.push_back(',');
			}
			result += String::number(node.urlID);
		}
		result += "]";
		std::string cvt_result = StringConvert::toStdString(result, CP_UTF8);
		auto res = new char[cvt_result.length() + 1];
		strcpy(res, cvt_result.c_str());
		return res;
	}

	DllExport const char *get_doc(Solver *app, int urlID) {
		auto &csv = app->getOutput().getCSV();
		String result;
		if (urlID < 1 || urlID >= csv.size()) {
			result = R"({"status":false,"reason":"index out of range"})";
		}
		else {
			auto &item = csv[urlID];
			String url;
			if (item.size() > 1) {
				url = item[1];
			}
			String title;
			if (item.size() > 4) {
				title = item[4];
			}
			String content;
			if (item.size() > 5) {
				content = item[5];
			}
			result = R"({"status":true,"url":")" + json_escape(url) + R"(","title":")" + json_escape(title) + R"(","content":")" + json_escape(content) + R"("})";
		}
		std::string cvt_result = StringConvert::toStdString(result, CP_UTF8);
		auto res = new char[cvt_result.length() + 1];
		strcpy(res, cvt_result.c_str());
		return res;
	}

	DllExport const char *divide_line(Solver *app, const char *line) {
		std::string inputLine(line);
		auto list = app->divideLine(StringConvert::fromStdString(inputLine, CP_UTF8));
		String result = "[";
		for (auto it = list.begin(); it != list.end(); ++it) {
			if (it != list.begin()) {
				result.push_back(',');
			}
			result.push_back('"');
			result += json_escape(*it);
			result.push_back('"');
		}
		result += "]";
		std::string cvt_result = StringConvert::toStdString(result, CP_UTF8);
		auto res = new char[cvt_result.length() + 1];
		strcpy(res, cvt_result.c_str());
		return res;
	}
}
