//
// Created by Gerwa on 2017/11/7.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_DOMNODE_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_DOMNODE_H

#include "LinkedList.h"
#include "BasicString.h"

struct DomNode {
    LinkedList<DomNode *> m_children;//for docunent and element
    LinkedList<Pair<String, String> > m_attributes;//for element
    String m_className;//for element
    String m_nodeName;//for element,text,comment
    enum NodeType {
        Document, Element, Text, Comment
    };
    NodeType m_nodeType;

    explicit DomNode(NodeType type) : m_nodeType(type) {}

    ~DomNode();

    void appendChild(DomNode *child);

    static int getEscapeCode(const String &str);

    static bool isSelfClosed(const String &tagName);

    static bool isNoEscape(const String &tagName);

    String innerHTML();
};

extern LinkedList<Pair<String, int>> HtmlEscapeList;
extern LinkedList<String> SelfClosingList;

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_DOMNODE_H
