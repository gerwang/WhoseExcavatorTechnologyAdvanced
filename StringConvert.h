//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H

#include "BasicString.h"
#include <string>
#include <cwchar>

class StringConvert {
public:
    static String fromStdString(const std::string &str, ByteArray localeString);

    static std::string toStdString(String wstr, ByteArray localeString);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_STRINGCONVERT_H
