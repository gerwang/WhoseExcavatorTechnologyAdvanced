//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_UTILITY_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_UTILITY_H

#include <utility>
#include "ArrayList.h"
#include "BasicString.h"

template<typename T>
struct Hasher {
    std::size_t operator()(const T &x) const {
        return static_cast<std::size_t>(*(&x));
    }
};

/*!
 * 特化的vector hash模板
 * @tparam T 元素的类型
 * @tparam Factor 进制
 */
template<typename T>
struct Hasher<BasicString<T>> {
    std::size_t operator()(const BasicString<T> &x) const {
        size_t res = 0;
        for (size_t i = 0; i < x.size(); i++) {
            res = res * 13 + x[i];
        }
        return res;
    }
};

template<typename T>
struct EqualTo {
    bool operator()(const T &a, const T &b) const {
        return a == b;
    }
};

template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;

    Pair() = default;

    Pair(const T1 &a, const T2 &b) : first(a), second(b) {}

    template<typename U, typename V>
    Pair(const Pair<U, V> &pr) { // NOLINT
        first = pr.first;
        second = pr.second;
    };
};

template<typename T1, typename T2>
Pair<T1, T2> makePair(const T1 &x, const T2 &y) {
    return Pair<T1, T2>(x, y);
};

template<typename T2>
Pair<String, T2> makePair(const char *a, const T2 &b) {
    return Pair<String, T2>(String(a), b);
};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_UTILITY_H
