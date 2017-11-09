//
// Created by Gerwa on 2017/11/7.
//
#include "HTMLParser.h"
#include "Stack.h"

const int HTMLParser::MaxTolerance = 10;

DomNode *HTMLParser::parseHTML(const String &html) {
    Stack<DomNode *> stack;
    int index = 0;
    stack.push(new DomNode(DomNode::Document));
    while (true) {
        index = nextNotSpace(html, index);
        if (index >= html.length()) {
            break;
        }
        DomNode *node;
        int stackDelta;
        index = parseNode(html, index, node, stackDelta);
        if (stackDelta == 1) {//open tag
            stack.top()->appendChild(node);
            stack.push(node);
        } else if (stackDelta == 0) {//self-closing tag
            stack.top()->appendChild(node);
        } else if (stackDelta == -1) {//close ta
            auto &container = stack.getContainer();
            int maxTolerance = container.size();
            if (maxTolerance > MaxTolerance) {
                maxTolerance = MaxTolerance;
            }

            bool ok = false;
            for (int i = 0; i < maxTolerance; i++) {//假设最多有maxTolerance个标签没有关闭
                if (container[container.size() - i - 1]->m_nodeName == node->m_nodeName) {
                    ok = true;
                    break;
                }
            }

            while (ok) {
                if (stack.top()->m_nodeName == node->m_nodeName) {
                    ok = false;
                }
                stack.pop();
            }

            delete node;
            node = nullptr;
        }
    }
    while (stack.top()->m_nodeType != DomNode::Document) {
        stack.pop();
    }
    return stack.top();
}

int HTMLParser::nextNotSpace(const String &html, int index) {
    while (index < html.length() && iswspace((wint_t) html[index])) {
        index++;
    }
    return index;
}

int HTMLParser::parseNode(const String &html, int index, DomNode *&node, int &stackDelta) {
    if (html.match("<--", static_cast<size_t>(index))) {//注释
        stackDelta = 0;
        int end_index = index;
        while (end_index < html.length() && !html.match("-->", static_cast<size_t>(end_index))) {
            end_index++;
        }
        index += 3;
        node = new DomNode(DomNode::Comment);
        node->m_nodeName = pureText(html, index, end_index);
        end_index += 3;
        return end_index;
    } else if (html.match("</", static_cast<size_t>(index))) {//关闭标签
        stackDelta = -1;
        int end_index = index;
        while (end_index < html.length() && !html.match(">", static_cast<size_t>(end_index))) {
            end_index++;
        }
        node = new DomNode(DomNode::Element);
        String name = html.substr(static_cast<unsigned int>(index + 2), static_cast<unsigned int>(end_index));
        while (iswspace(static_cast<wint_t>(name.back()))) {
            name.pop_back();
        }
        node->m_nodeName = std::move(name);
        end_index++;
        return end_index;
    } else if (html.match("<", static_cast<size_t>(index))) {//开始标签/自关闭标签
        stackDelta = 1;

        //parse TagName
        int end_index = index;
        while (end_index < html.length() && html[end_index] != '>' &&
               html[end_index] != '/' && !iswspace((wint_t) html[end_index])) {
            end_index++;
        }
        node = new DomNode(DomNode::Element);
        node->m_nodeName = html.substr(static_cast<unsigned int>(index + 1), static_cast<unsigned int>(end_index));
        if (DomNode::isSelfClosed(node->m_nodeName)) {
            stackDelta = 0;
        }
        //

        //parse normal tag
        while (true) {
            index = nextNotSpace(html, index);
            if (html[index] == '/') {
                stackDelta = 0;
                index++;
            } else if (html[index] == '>') {
                end_index = index + 1;
                break;
            } else {
                end_index = index;
                while (end_index < html.length() && !iswspace((wint_t) html[end_index]) && html[end_index] != '=' &&
                       html[end_index] != '>' && html[end_index] != '/') {
                    end_index++;
                }
                String key = html.substr(static_cast<unsigned int>(index), static_cast<unsigned int>(end_index));
                String value = "";
                if (html[end_index] == '=') {
                    index = end_index + 1;
                    while (index < html.length() && html[index] != '"') {
                        index++;
                    }
                    end_index = index + 1;
                    while (end_index < html.length() && html[end_index] != '"') {
                        end_index++;
                    }
                    value = html.substr(static_cast<unsigned int>(index + 1), static_cast<unsigned int>(end_index));
                }
                if (key == "class") {
                    node->m_className = value;
                } else {
                    node->m_attributes.push_back(makePair(key, value));
                }
                index = end_index + 1;
            }
        }
        //parse normal tag end


        if (DomNode::isNoEscape(node->m_nodeName)) {
            stackDelta = 0;
            index = nextNotSpace(html, end_index);
            String end_string = "<" + node->m_nodeName + "/>";
            while (end_index < html.length() && !html.match(end_string, static_cast<size_t>(end_index))) {
                end_index++;
            }
            auto textNode = new DomNode(DomNode::Text);
            textNode->m_nodeName = html.substr(static_cast<unsigned int>(index), static_cast<unsigned int>(end_index));
            node->appendChild(textNode);
            end_index += end_string.length();
            return end_index;
        } else {
            return end_index;
        }

    } else {//纯文本
        stackDelta = 0;
        int end_index = index;
        while (end_index < html.length() && html[end_index] != '<') {
            end_index++;
        }
        node = new DomNode(DomNode::Text);
        node->m_nodeName = pureText(html, index, end_index);
        return end_index;
    }
}

String HTMLParser::pureText(const String &html, int index, int end_index) {
    String res;
    while (index < end_index) {
        if (html.match("&#", static_cast<size_t>(index))) {
            int semi_index = nextSemiColon(html, index);
            int textCode = 0;
            index += 2;
            while (index < semi_index) {
                textCode = textCode * 10 + html[index] - '0';
                index++;
            }
            res.push_back(static_cast<wchar_t >(textCode));
            index = semi_index + 1;
        } else if (html.match("&", static_cast<size_t>(index))) {
            int semi_index = nextSemiColon(html, index);
            int textCode = DomNode::getEscapeCode(html.substr(static_cast<unsigned int>(index + 1),
                                                              static_cast<unsigned int>(semi_index)));
            if (textCode == -1) {
                res.push_back(html[index]);
                index++;
            } else {
                res.push_back(static_cast<wchar_t>(textCode));
                index = semi_index + 1;
            }
        } else {
            res.push_back(html[index]);
            index++;
        }
    }
}

int HTMLParser::nextSemiColon(const String &html, int index) {
    while (index < html.length() && html[index] != ';') {
        index++;
    }
    return index;
}
