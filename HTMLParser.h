//
// Created by Gerwa on 2017/11/7.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_HTMLPARSER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_HTMLPARSER_H

#include "DomNode.h"

class HTMLParser {
    static const int MaxTolerance;

    static int nextSemiColon(const String &html, int index);

    static int nextNotSpace(const String &html, int index);

public:
    DomNode *parseHTML(const String &html);

    static int parseNode(const String &html, int index, DomNode *&node, int &stackDelta);

    static String pureText(const String &html, int index, int end_index);
};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_HTMLPARSER_H
