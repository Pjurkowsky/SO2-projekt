#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fridge.h"
#include "clock.h"

class Garfield {

public:
    Garfield(Fridge &fridge, Clock &clock, std::mutex& mutex, std::condition_variable &cv, Window* windows);
    void consume();

private:
    std::mutex &m_mutex;
    std::condition_variable &m_cv;
    Fridge &m_fridge;
    Window *m_windows;
    Clock &m_clock;

    bool m_isSleeping = false;



    const char* customArt[15] = {
         "             --      --",
        "            .:\"  | .:'\" |",
        "          --  ___   ___  -",
        "        /:.  /  .\\ /.  \\ .\\",
        "       |:|. ;\\___/O\\___/  :|",
        "       |:|. |  `__|__'  | .|",
        "       |:|.  \\_,     ,_/  /",
        "        \\______       |__/",
        "         |:.           \\",
        "        /.:,|  |        \\",
        "       /.:,.|  |         \\",
        "       |::.. \\_;_\\-;       |",
        " _____|::..    .::|       |",
        "/   ----,     .::/__,    /__,",
        "\\_______|,...____;_;_|../_;_|"
    };

    void eatLasagna();
};