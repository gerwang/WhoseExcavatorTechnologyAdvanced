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
    /*!
     * 清空当前对象，并将文件中的内容加载到当前对象中
     * @param fileName 文件名
     * @attention 没有测试文件名对中文的支持性
     */
    void load(const ByteArray &fileName);

    /*!
     * 将当前的csv内容保存到对应的文件中
     * @param fileName 保存的文件名
     */
    void save(String fileName);

    /*!
     * * @return 当前对象的csv容器
     */
    ArrayList<ArrayList<String>> &getCSV();
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_CSVHANDLER_H
