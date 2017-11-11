//
// Created by Gerwa on 2017/11/10.
//
/*!
 * @brief 分词
 */
#include "WordDivider.h"
#include "StringConvert.h"
#include "HTMLParser.h"

/*!
 * 加载词典
 * @param fileName 词典的文件名（相对路径）
 */
void WordDivider::load(const ByteArray &fileName, HashSet<String> &currentDict) {
    String wordList = StringConvert::fromFile(fileName);
    int index = 0;
    while (index < wordList.length()) {
        index = HTMLParser::nextNotSpace(wordList, index);
        int end_index = index;
        while (end_index < wordList.length() &&
               !iswspace(static_cast<wint_t>(wordList[end_index]))) {
            end_index++;
        }
        currentDict.insert(wordList.substr(static_cast<unsigned int>(index),
                                           static_cast<unsigned int>(end_index)));
        if (max_length < end_index - index) {
            max_length = end_index - index;
        }
        index = end_index;
    }
}

/*!
 * 分词主过程
 * @attention 未出现在词典中的字符会被忽略掉
 * @param text 待分词的文本
 * @return 返回单词的链表，按照出现顺序排列
 */
LinkedList<String> WordDivider::divideWords(const String &text) const {
    LinkedList<String> res;
    for (int i = text.length(); i > 0; i--) {
        int len = std::min(max_length, i);
        for (int j = len; j > 0; j--) {
            String sub = text.substr(static_cast<unsigned int>(i - j),
                                     static_cast<unsigned int>(i));
            if (stopWords.count(sub) > 0) {
                i -= j - 1;
                break;
            }
            if (dict.count(sub) > 0) {
                res.push_front(sub);
                i -= j - 1;
                break;
            }
        }
        /*
        if (!done) {
            if (text[i - 1] >= 128) {//no ascii char
                res.push_front(text.substr(static_cast<unsigned int>(i - 1), static_cast<unsigned int>(i)));
            }
        }*/
    }
    return res;
}

void WordDivider::loadDict(const ByteArray &fileName) {
    load(fileName, dict);
}

void WordDivider::loadStopWords(const ByteArray &fileName) {
    load(fileName, stopWords);
}
