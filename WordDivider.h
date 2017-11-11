//
// Created by Gerwa on 2017/11/10.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_DICTIONARY_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_DICTIONARY_H

#include "HashSet.h"
#include "BasicString.h"

class WordDivider {
    HashSet<String> dict;
    HashSet<String> stopWords;
    int max_length;
public:

    WordDivider() : max_length(0) {}

    virtual ~WordDivider() = default;

    void load(const ByteArray &fileName, HashSet<String> &currentDict);

    void loadDict(const ByteArray &fileName);

    void loadStopWords(const ByteArray &fileName);

    LinkedList<String> divideWords(const String &text) const;
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_DICTIONARY_H
