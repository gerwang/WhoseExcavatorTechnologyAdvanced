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
    /*!
     * 将char形式的字符串转换成宽字符串
     * @param str 单字节存储的字符串
     * @param codePage 代码页，默认为ANSI
     * @return 转换后的宽字符串
     * @note utf-8的codepage是CP_UTF8
     */
    static String fromStdString(const std::string &str, UINT codePage = CP_ACP);

    /*!
     * 将宽字符串转换成窄字符串
     * @param wstr
     * @param codePage
     * @return
     */
    static std::string toStdString(String wstr, UINT codePage = CP_ACP);

    /*!
     * @attention 不支持在代码中写中文的文件名
     * @param fileName
     * @return
     */
    static String fromFile(ByteArray fileName, UINT codePage = CP_ACP);

    /*!
     * 清空文件，将字符串保存到文件当中
     * @param output
     * @param fileName
     * @param codePage
     */
    static void toFile(const String &output, ByteArray fileName, UINT codePage = CP_ACP);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H
