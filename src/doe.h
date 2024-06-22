#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "window.h"
#include "fridge.h"
#include "clock.h"

class Doe
{
public:
    Doe(Fridge &fridge, Clock &clock, std::mutex &mutex, std::condition_variable &cv, Window *windows);
    void exists();
private:
    std::mutex &m_mutex;
    std::condition_variable &m_cv;
    Fridge &m_fridge;
    Window *m_windows;
    Clock &m_clock;

void eatLasagna();
};