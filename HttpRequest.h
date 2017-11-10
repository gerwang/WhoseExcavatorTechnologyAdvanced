//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_HTTPREQUEST_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_HTTPREQUEST_H

#include "BasicString.h"

class HttpRequest {
public:
    /*!
     * 发送一个get请求，返回得到的html字符串
     * @param url 请求的网址
     * @return html文档
     */
    String get(const String &url);

    /*!
     * Winsock的初始化
     */
    static void startUp();

    /*
     * Winsock的清理
     */
    static void tearDown();
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_HTTPREQUEST_H
