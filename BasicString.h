//
// Created by Gerwa on 2017/11/5.
//
#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_STRING_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_STRING_H


#include "ArrayList.h"
#include "Stack.h"


template<typename CharT>
class BasicString : public ArrayList<CharT> {
public:
    typedef ArrayList<CharT> parent_type;
    typedef BasicString<CharT> instance_type;
    typedef typename parent_type::iterator iterator;
    typedef typename parent_type::const_iterator const_iterator;
    typedef typename parent_type::size_type size_type;

    /*!
     * 返回下标为[startIndex,endIndex)的子串
     * @param startIndex
     * @param endIndex 不包含自身
     * @return 新构建的子串
     */
    instance_type substr(size_type startIndex, size_type endIndex) const {
        BasicString res;
        for (size_type i = startIndex; i < endIndex; i++) {
            res.push_back(this->operator[](i));
        }
        return std::move(res);
    }

    BasicString() {}

    template<typename OtherCharT>
    BasicString(OtherCharT *cstr) {// NOLINT
        while (*cstr != OtherCharT('\0')) {
            this->push_back(CharT(*cstr));
            cstr++;
        }
    }

    template<typename OtherCharT>
    BasicString(const BasicString<OtherCharT> &other) {// NOLINT
        for (size_t i = 0; i < other.size(); i++) {
            this->push_back(CharT(other[i]));
        }
    }

    /*!
     * @attention 不优美的实现，在修改了字符串之后一定要重新调用c_str()来保证最后有终止字符
     * @return C风格的字符串
     */
    CharT *c_str() {
        this->push_back(CharT('\0'));
        this->pop_back();
        return this->begin();
    }

    size_type length() const {
        return this->size();
    }

    /*!
     * 以*this为文本串，用KMP算法实现的匹配，返回第一个出现位置的下标
     * @param pattern 待匹配的模板串
     * @return 第一个出现的位置的下标，如果没有匹配返回size()
     */
    size_type find(const instance_type &pattern) const {
        size_type *fail = new size_type[pattern.length() + 2];
        /*
         * k=fail[i]表示最大的k满足substr[0,k)==substr[i-k,i)且str[k]!=str[i]
         * k=fail[i+1] substr[0,k)==substr[i-k,i+1) && str[k]!=str[i+1]
         * 若不存在即为0
         */
        fail[0] = fail[1] = 0;
        for (size_type i = 1; i < pattern.length(); i++) {
            size_type j = fail[i];
            while (j != 0 && pattern[i] != pattern[j]) {
                j = fail[j];
            }
            if (pattern[i] == pattern[j]) {
                if (i + 1 == pattern.length() || pattern[i + 1] != pattern[j + 1]) {
                    fail[i + 1] = j + 1;
                } else {
                    fail[i + 1] = fail[j + 1];//knuth optimization
                }
            } else {
                fail[i + 1] = 0;
            }
        }
        size_type res = this->size();
        size_type j = 0;
        for (size_type i = 0; i < length(); i++) {
            while (j != 0 && this->operator[](i) != pattern[j]) {
                j = fail[j];
            }
            if (this->operator[](i) == pattern[j]) {
                j++;
                if (j == pattern.length()) {
                    res = i + 1 - pattern.length();
                    break;
                }
            }
        }
        delete[] fail;
        return res;
    }

    static instance_type number(int x) {
        Stack<CharT> stack;
        bool negative = false;
        if (x < 0) {
            x = -x;
            negative = true;
        }
        while (x != 0) {
            stack.push(CharT('0') + x % 10);
            x /= 10;
        }
        if (negative) {
            stack.push(CharT('-'));
        }
        instance_type res;
        while (!stack.empty()) {
            res.push_back(stack.top());
            stack.pop();
        }
        return res;
    }

    template<typename OtherCharT>
    instance_type &operator+=(OtherCharT *other) {
        while (*other) {
            this->push_back(*(other++));
        }
        return *this;
    }

    instance_type &operator+=(const instance_type &other) {
        for (auto &x:other) {
            this->push_back(x);
        }
        return *this;
    }

    bool match(const instance_type &pattern, size_t start_index = 0) const {
        if (start_index + pattern.size() > this->size()) {
            return false;
        }
        for (size_t i = 0; i < pattern.size(); i++) {
            if (this->operator[](start_index + i) != pattern[i]) {
                return false;
            }
        }
        return true;
    }
};

template<typename CharT1, typename CharT2>
bool operator==(const BasicString<CharT1> &a, const BasicString<CharT2> &b) {
    if (a.length() != b.length()) {
        return false;
    }
    for (size_t i = 0; i < a.length(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
};

template<typename CharT1, typename CharT2>
bool operator==(const BasicString<CharT1> &a, const CharT2 *b) {
    return a == BasicString<CharT1>(b);
};

template<typename CharT1, typename CharT2>
bool operator==(const CharT1 *a, const BasicString<CharT2> &b) {
    return BasicString<CharT2>(a) == b;
};

template<typename CharT>
std::basic_ostream<CharT> &operator<<(std::basic_ostream<CharT> &out, BasicString<CharT> string) {
    out << string.c_str();
    return out;
}

template<typename CharT>
BasicString<CharT> operator+(const BasicString<CharT> &a, const BasicString<CharT> &b) {
    BasicString<CharT> res(a);
    for (auto &x:b) {
        res.push_back(x);
    }
    return res;
}

template<typename CharT1, typename CharT2>
BasicString<CharT1> operator+(const BasicString<CharT1> &a, const BasicString<CharT2> &b) {
    return a + BasicString<CharT1>(b);
};

template<typename CharT1, typename CharT2>
BasicString<CharT1> operator+(const BasicString<CharT1> &a, const CharT2 *b) {
    return a + BasicString<CharT1>(b);
};

template<typename CharT1, typename CharT2>
BasicString<CharT2> operator+(const CharT1 *a, const BasicString<CharT2> &b) {
    return BasicString<CharT2>(a) + b;
};

typedef BasicString<wchar_t> String;
typedef BasicString<char> ByteArray;

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_STRING_H
