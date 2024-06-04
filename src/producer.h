#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fridge.h"

class Producer {
public:
    Producer(Fridge &fridge, std::mutex &mutex, std::condition_variable &cv);

    void produce();

private:
    static int number_of_producers;
    int m_id;
    std::mutex& m_mutex;
    std::condition_variable &m_cv;
    Fridge &m_fridge;

    void addLasagna();
};