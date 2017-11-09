//
// Created by Gerwa on 2017/11/6.
//

#include "StringConvert.h"
#include <locale>
#include <fstream>
#include <cstring>

/*!
 *
 * @param str
 * @param localeString
 * @return
 */
String StringConvert::fromStdString(const std::string &str, UINT codePage) {
    int len = MultiByteToWideChar(codePage, 0, str.c_str(), -1, nullptr, 0);
    auto w_buffer = new wchar_t[len];
    MultiByteToWideChar(codePage, 0, str.c_str(), -1, w_buffer, len);
    String res(w_buffer);
    delete[] w_buffer;
    return res;
}

std::string StringConvert::toStdString(String wstr, UINT codePage) {
    int len = WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, nullptr, 0, nullptr, FALSE);
    auto c_buffer = new char[len];
    WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, c_buffer, len, nullptr, FALSE);
    std::string res(c_buffer);
    delete[] c_buffer;
    return res;
}

String StringConvert::fromFile(ByteArray fileName) {
    std::ifstream fin(fileName.c_str());
    std::string str((std::istreambuf_iterator<char>(fin)),
                    std::istreambuf_iterator<char>());
    return fromStdString(str);
}

void StringConvert::toFile(const String &output, ByteArray fileName) {
    std::string converted(toStdString(output));
    std::ofstream fout(fileName.c_str());
    fout << converted;
}
