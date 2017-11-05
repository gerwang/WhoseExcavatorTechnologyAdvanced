//
// Created by Gerwa on 2017/11/5.
//

#include <iostream>
#include "Test.h"
#include "ArrayList.h"
#include "BasicString.h"
#include "Stack.h"
#include "LinkedList.h"

void Test::testVector() {
    ArrayList<int> vector;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector.assign(a, a + 10);
    for (int i = 0; i < 10; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << vector.size() << vector.capacity() << vector.empty() << std::endl;
    vector.erase(vector.begin() + 1);
    vector.push_back(11);
    wcout << vector << std::endl;
    for (int i = 0; i < 100; i++) {
        vector.push_back(i);
    }
    std::cout << vector << std::endl;
}

void Test::testString() {
    BasicString<char> string("abcabcda"), pattern("abcd");
    std::cout << string.find(pattern);
    BasicString<char> other(string);
    string[0] = 'b';
    std::cout << other << std::endl;
}

void Test::testStack() {
    Stack<int> stack;
    for (int i = 0; i < 5; i++) {
        stack.push(i);
    }
    while (!stack.empty()) {
        stack.top() += 10;
        cout << stack.top() << endl;
        stack.pop();
    }
}

void Test::testLinkedList() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> list(a, a + 10);
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    std::cout << list << std::endl;
}
