//
// Created by Gerwa on 2017/12/9.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int n) : canStop(false) {
    for (int i = 0; i < n; i++) {
        workers.push_back(std::thread([this]() {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this]() {
                        return canStop || !tasks.empty();
                    });
                    if (canStop && tasks.empty()) {
                        return;
                    }
                    task = std::move(*tasks.begin());
                    tasks.erase(tasks.begin());
                }
                task();
            }
        }));
    }
}

ThreadPool::~ThreadPool() {
    canStop = true;
    condition.notify_all();
    for (auto &worker:workers) {
        worker.join();
    }
}

void ThreadPool::addTask(std::function<void()> &&task) {
    std::unique_lock<std::mutex> lock(queueMutex);
    tasks.push_back(std::move(task));
    condition.notify_one();
}
