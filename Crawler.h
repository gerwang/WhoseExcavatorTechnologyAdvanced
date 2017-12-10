//
// Created by Gerwa on 2017/11/9.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_CRAWELER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_CRAWELER_H


#include "ArrayList.h"
#include "BasicString.h"

class Crawler {
public:
    /*!
     * 爬取并解析网址并返回需要的信息
     * @param url  网址
     * @return 需要的信息
     */
    ArrayList<String> crawl(const String &url, int fileIndex);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_CRAWELER_H
