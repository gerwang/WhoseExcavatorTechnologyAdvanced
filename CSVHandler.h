//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_CSVHANDLER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_CSVHANDLER_H

#include "LinkedList.h"
#include "ArrayList.h"
#include "BasicString.h"

class CSVHandler {
    ArrayList<ArrayList<String>> csv;
public:
    void load(const ByteArray &fileName);

    void save(String fileName);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_CSVHANDLER_H
