//
// Created by Gerwa on 2017/11/5.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_STACK_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_STACK_H

#include "Vector.h"

template<typename T, typename Container=Vector<T> >
class Stack {
    typedef T value_type;
private:
    Container container;
public:
    void push(value_type &&elem) {
        container.push_back(std::move(elem));
    }

    void push(const value_type &elem) {
        container.push_back(elem);
    }

    void pop() {
        container.pop_back();
    }

    value_type &top() {
        return container.back();
    }

    bool empty() const {
        return container.empty();
    }
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_STACK_H
