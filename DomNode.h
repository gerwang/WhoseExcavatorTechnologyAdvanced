//
// Created by Gerwa on 2017/11/7.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_DOMNODE_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_DOMNODE_H

#include "LinkedList.h"
#include "BasicString.h"

struct DomNode {
    LinkedList<DomNode *> m_children;///< 儿子结点 for docunent and element
    LinkedList<Pair<String, String> > m_attributes;///< 属性列表 for element
    String m_className;///< 类名，该字符串中可以有多个类名 for element
    String m_nodeName;///< 标签名或标签值 for element,text,comment
    enum NodeType {
        Document, Element, Text, Comment
    };
    NodeType m_nodeType;///< 标签类型

    explicit DomNode(NodeType type) : m_nodeType(type) {}

    virtual ~DomNode();

    /*!
     * 当child添加到儿子节点的列表中
     * @param child 待加入的儿子结点
     */
    void appendChild(DomNode *child);

    /*!
     * * @param str 转义过的字符串
     * @return 对应的unicode值
     */
    static int getEscapeCode(const String &str);

    /*!
     * * @param tagName 标签名
     * @return 是否是自闭合的标签
     */
    static bool isSelfClosed(const String &tagName);

    /*!
     * * @param tagName 标签名
     * @return 是否是代码标签
     */
    static bool isNoEscape(const String &tagName);

    String innerHTML();

    String text();

    /*!
     * 用先序遍历得到子树的文本，添加到text中
     * @param text 保存结果的字符串
     */
    void retrieveText(String &text);

    /*!
     * 返回第一个儿子
     * @return 第一个儿子
     */
    DomNode *firstChild();
};

extern const LinkedList<Pair<String, int>> HtmlEscapeList;
extern const LinkedList<String> SelfClosingList;

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_DOMNODE_H
