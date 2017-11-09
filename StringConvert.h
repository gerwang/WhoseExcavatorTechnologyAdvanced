//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H

#include "BasicString.h"
#include <string>
#include <cwchar>
#include <windows.h>

class StringConvert {
public:
    static String fromStdString(const std::string &str, UINT codePage = CP_ACP);

    static std::string toStdString(String wstr, UINT codePage = CP_ACP);

    /*!
     * @attention 不支持在代码中写中文的文件名
     * @param fileName
     * @return
     */
    static String fromFile(ByteArray fileName);

    static void toFile(const String &output, ByteArray fileName);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H
