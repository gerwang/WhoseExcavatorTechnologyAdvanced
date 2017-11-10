//
// Created by Gerwa on 2017/11/7.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_HTMLPARSER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_HTMLPARSER_H

#include "DomNode.h"

class HTMLParser {
    static const int MaxTolerance;

    /*!
     * 找到下一个出现的分号
     * @param html 待查询的html字符串
     * @param index 当前的小标
     * @param end_index 寻找的右界
     * @return 从当前位置开始（包括当前位置）下一个分号的位置，如果没有返回html.length()
     */
    static int nextSemiColon(const String &html, int index, int end_index);

public:
    /*!
     * 找到下一个出现的非空字符
     * @param html 待查询的html字符串
     * @param index 当前的小标
     * @param end_index 寻找的右界
     * @return 从当前位置开始（包括当前位置）下一个非空字符的位置，如果没有返回html.length()
     */
    static int nextNotSpace(const String &html, int index);

    /*!
     * @attention 返回的指针需要手动delete掉才能释放
     * @param html 待解析的html字符串
     * @return DOM树的根节点
     */
    DomNode *parseHTML(const String &html);

    /*!
     * 从index开始解析一个DOM树结点
     * @param html 待解析的html字符串
     * @param index 当前位置
     * @param node 存放返回的结点
     * @param stackDelta 栈的变化量，指示这个结点是一个开始标签，结束标签还是自闭合标签
     * @return index的下一个位置
     */
    static int parseNode(const String &html, int index, DomNode *&node, int &stackDelta);

    /*!
     * 将html中的转义字符去转义化后返回纯文本
     * @param html 待解析的html字符串
     * @param index 左区间
     * @param end_index 右区间，不包括本身
     * @return 解析后的纯文本
     */
    static String pureText(const String &html, int index, int end_index);
};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_HTMLPARSER_H
