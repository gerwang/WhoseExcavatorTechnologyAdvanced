//
// Created by Gerwa on 2017/12/9.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_THREADPOOL_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_THREADPOOL_H

#include "ArrayList.h"
#include "LinkedList.h"
#include <condition_variable>
#include <thread>
#include <atomic>

class ThreadPool {
    std::condition_variable_any condition;
    ArrayList<std::thread> workers;
    LinkedList<std::function<void()>> tasks;
    std::atomic_bool canStop;
    std::mutex queueMutex;
public:
    explicit ThreadPool(int n = std::thread::hardware_concurrency());

    void addTask(std::function<void()> &&task);

    virtual ~ThreadPool();
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_THREADPOOL_H
