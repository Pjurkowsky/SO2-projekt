#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fridge.h"

class Garfield {

public:
    Garfield(Fridge &fridge, std::mutex& mutex, std::condition_variable &cv);
    void consume();

private:
    std::mutex &m_mutex;
    std::condition_variable &m_cv;
    Fridge &m_fridge;

    void eatLasagna();


};