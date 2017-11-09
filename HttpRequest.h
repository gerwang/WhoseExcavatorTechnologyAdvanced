//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_HTTPREQUEST_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_HTTPREQUEST_H

#include "BasicString.h"

class HttpRequest {
public:
    String get(const String &url);

    static void startUp();

    static void tearDown();
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_HTTPREQUEST_H
