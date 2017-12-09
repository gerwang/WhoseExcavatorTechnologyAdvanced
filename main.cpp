#include <iostream>
#include "Test.h"
#include "CSVHandler.h"
#include "Crawler.h"
#include "HttpRequest.h"
#include "HTMLParser.h"
#include "WordDivider.h"
#include "ThreadPool.h"

/*!
 * 使用给定的分词器处理数据
 * @param url 网址
 * @param result 存放结果的向量
 * @param divider 分词器
 * @param index 序号
 */

std::mutex output_mutex;

void work(const String &url, ArrayList<String> &result, const WordDivider &divider, int index) {
    {
        std::unique_lock<std::mutex> lock(output_mutex);
        std::cout << "Starting " << index << std::endl;
    }
    result.clear();
    result.push_back(String::number(index));
    result.push_back(url);
    result += Crawler().crawl(url);
    if (result.size() == 9) {
        auto titleWords = divider.divideWords(result[4]);
        auto contentWords = divider.divideWords(result[5]);
        String res;
        for (auto &word:titleWords) {
            res += word;
            res += " ";
        }
        for (auto &word:contentWords) {
            res += word;
            res += " ";
        }
        result.push_back(res);
    }
    {
        std::unique_lock<std::mutex> lock(output_mutex);
        std::cout << "Complete " << index << std::endl;
    }
}

void solve() {
    WordDivider wordDivider;
    wordDivider.loadDict("dictionary.dic");
    wordDivider.loadDict("term.dic");
    wordDivider.loadStopWords("stopword.dic");
    CSVHandler handler;
    handler.load("input/url.csv");
    auto &csv = handler.getCSV();
    CSVHandler output;
    auto &csvout = output.getCSV();
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
        ThreadPool pool;
        for (int row = 1; row < csv.size(); row++) {
            const String &url = csv[row][1];
            ArrayList<String> &backPtr = csvout[row];
            pool.addTask([url, &backPtr, &wordDivider, row]() {
                work(url, backPtr, wordDivider, row);
            });
        }
    }
    output.save("input/result.csv");
}

int main() {
    HttpRequest::startUp();
    solve();
    HttpRequest::tearDown();
    return 0;
}