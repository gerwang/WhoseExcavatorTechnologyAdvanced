//
// Created by Gerwa on 2017/11/6.
//

#include "StringConvert.h"
#include <locale>

String StringConvert::fromStdString(const std::string &str, ByteArray localeString) {
    std::setlocale(LC_ALL, localeString.c_str());
    size_t len;
    mbstowcs_s(&len, nullptr, 0, str.c_str(), str.length());
    len++;//see http://en.cppreference.com/w/c/string/multibyte/wcstombs
    auto *temp = new wchar_t[len];
    mbstowcs_s(&len, temp, len, str.c_str(), str.length());
    String res(temp);
    delete[] temp;
    return res;
}

std::string StringConvert::toStdString(String wstr, ByteArray localeString) {
    std::setlocale(LC_ALL, localeString.c_str());
    size_t len;
    wcstombs_s(&len, nullptr, 0, wstr.c_str(), 0);
    len++;
    auto *temp = new char[len];
    wcstombs_s(&len, temp, len, wstr.c_str(), len);
    std::string res(temp);
    delete[] temp;
    return res;
}
