#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fridge.h"
#include "producer.h"
#include "garfield.h"
#include "doe.h"
#include "clock.h"

#include <ncurses.h>
#include "window.h"

void startSimulation(Fridge &fridge, Window* windows) {

    std::mutex mutex;
    std::condition_variable cv;

    Clock clock(windows);

    Producer producer(fridge, clock, mutex, cv, windows);
    Garfield garfield(fridge, clock, mutex, cv, windows);
    Doe doe(fridge, clock, mutex, cv, windows);

    std::thread producerThread(&Producer::produce, &producer);
    std::thread garfieldThread(&Garfield::consume, &garfield);
    std::thread doeThread(&Doe::exists, &doe);
    std::thread clockThread(&Clock::run, &clock);

    producerThread.join();
    garfieldThread.join();
    doeThread.join();
    clockThread.join();
}


int main() {
    int capacity = 64;

    initscr();            
    start_color();
    use_default_colors();
    curs_set(0);          
    refresh();            
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int left_width = xMax * 3 / 4;
    int right_width = xMax - left_width;
    int upper_height = yMax * 3 / 5;
    int lower_height = yMax - upper_height;
    Window windows[3] = {
        Window(left_width, upper_height, 0, 0, ""), // left
        Window(right_width, upper_height, left_width, 0, "fridge"), // right
        Window(xMax, lower_height, 0, upper_height, "console") // bottom
    };
    

    Fridge fridge(capacity, windows);
    startSimulation(fridge, windows);
    endwin();          


            

    return 0;
}