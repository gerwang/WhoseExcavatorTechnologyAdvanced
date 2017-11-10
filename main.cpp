#include <iostream>
#include "Test.h"
#include "CSVHandler.h"
#include "Crawler.h"
#include "HttpRequest.h"
#include "HTMLParser.h"
#include "WordDivider.h"

/*!
 * 使用给定的分词器处理数据
 * @param url 网址
 * @param result 存放结果的向量
 * @param divider 分词器
 * @param index 序号
 */
void work(const String &url, ArrayList<String> &result, const WordDivider &divider, int index) {
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
}

int main() {
    HttpRequest::startUp();
    WordDivider wordDivider;
    wordDivider.loadDict("dictionary.dic");
    wordDivider.loadDict("term.dic");
    CSVHandler handler;
    handler.load("url.csv");
    auto &csv = handler.getCSV();
    CSVHandler output;
    output.getCSV().resize(1);
    output.getCSV()[0].push_back(L"序号");
    output.getCSV()[0].push_back(L"网址");
    output.getCSV()[0].push_back(L"发帖大类");
    output.getCSV()[0].push_back(L"发帖小类");
    output.getCSV()[0].push_back(L"发帖标题");
    output.getCSV()[0].push_back(L"发帖内容");
    output.getCSV()[0].push_back(L"发帖人");
    output.getCSV()[0].push_back(L"发帖日期");
    output.getCSV()[0].push_back(L"发帖类型");
    output.getCSV()[0].push_back(L"分词结果");
    for (int row = 1; row < csv.size(); row++) {
        const String &url = csv[row][1];
        ArrayList<String> holder;
        work(url, holder, wordDivider, row);
        output.getCSV().push_back(std::move(holder));
        std::cout << "Complete " << row << std::endl;
    }
    output.save("result.csv");
    HttpRequest::tearDown();
    return 0;
}