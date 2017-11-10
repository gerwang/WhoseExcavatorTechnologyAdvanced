//
// Created by Gerwa on 2017/11/7.
//

#include "cQuery.h"
#include "ArrayList.h"

cQuery &cQuery::clas(const String &name) {
    m_classNames.push_back(name);
    return *this;
}

cQuery &cQuery::attr(const String &key, const String &value) {
    m_attributes.push_back(makePair(key, value));
    return *this;
}

cQuery &cQuery::tag(const String &name) {
    m_tagNames.push_back(name);
    return *this;
}

void cQuery::select(DomNode *root, ArrayList<DomNode *> &results) {
    if (checkNode(root)) {
        results.push_back(root);
    }
    for (const auto &child:root->m_children) {
        select(child, results);
    }
}

bool cQuery::checkNode(const DomNode *node) {
    if (!m_tagNames.empty() && node->m_nodeType != DomNode::Element) {
        return false;
    }
    for (const auto &tag:m_tagNames) {
        if (node->m_nodeName != tag) {
            return false;
        }
    }
    for (const auto &className:m_classNames) {
        if (node->m_className.find(className) == node->m_className.length()) {
            return false;
        }
    }
    for (const auto &pair:m_attributes) {
        auto it = node->m_attributes.begin();
        while (it != node->m_attributes.end() && it->first != pair.first) {
            ++it;
        }
        if (it == node->m_attributes.end() ||
            (pair.second.length() > 0 && it->second != pair.second)) {//如果pair.second留空，只需要有这个属性即可
            return false;
        }
    }
    return true;
}

cQuery &cQuery::pick(int index) {
    DomNode *remain = m_results[index];
    m_results.clear();
    m_results.push_back(remain);
    return *this;
}

cQuery &cQuery::get() {
    ArrayList<DomNode *> next_result;
    for (auto root:m_results) {
        select(root, next_result);
    }
    m_results = std::move(next_result);
    return *this;
}

cQuery::cQuery(DomNode *nav) {
    m_results.push_back(nav);
}
