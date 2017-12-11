//
// Created by Gerwa on 2017/12/11.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_SOLVER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_SOLVER_H

#include "WordDivider.h"
#include "CSVHandler.h"
#include "AvlMap.h"

struct DocNode {
    int urlID, occurTime;

    DocNode() {}

    DocNode(int urlID, int occurTime) : urlID(urlID), occurTime(occurTime) {}
};

struct DocCounter {
    LinkedList<DocNode> docs;

    void addTime(int id, int t) {
        for (auto it = docs.begin(); it != docs.end(); ++it) {
            if (it->urlID == id) {
                it->occurTime += t;
                return;
            }
        }
        docs.push_back(DocNode(id, t));
    }
};

class Solver {

    CSVHandler handler, output;

    AvlMap<String, DocCounter> treeMap;

/*!
 * 使用给定的分词器处理数据
 * @param url 网址
 * @param result 存放结果的向量
 * @param divider 分词器
 * @param urlID 序号
 */
    void work(const String &url, ArrayList<String> &result, const WordDivider &divider, int urlID);

public:
    void loadPages();

    ArrayList<DocNode> searchQuery(const std::string &inpueLine);

    void solveConsole();

    void outputDebug();
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_SOLVER_H
