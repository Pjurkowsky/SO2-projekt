#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fridge.h"
#include "clock.h"

class Producer {
public:
    Producer(Fridge &fridge, Clock &clock, std::mutex &mutex, std::condition_variable &cv, Window* windows);

    void produce();

private:
    static int number_of_producers;
    int m_id;
    std::mutex& m_mutex;
    std::condition_variable &m_cv;
    Fridge &m_fridge;
    Window *m_windows;
    Clock &m_clock;

    bool m_isWorking = true;

  

    void addLasagna();
};