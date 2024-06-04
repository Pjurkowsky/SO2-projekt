#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "fridge.h"
#include "producer.h"
#include "garfield.h"

#include <ncurses.h>


void startSimulation(int capacity) {

    std::mutex mutex;
    std::condition_variable cv;

    Fridge fridge(capacity);

    Producer producer(fridge, mutex, cv);
    Garfield garfield(fridge, mutex, cv);

    std::thread producerThread(&Producer::produce, &producer);
    std::thread garfieldThread(&Garfield::consume, &garfield);

    std::this_thread::sleep_for(std::chrono::seconds(10));


    producerThread.join();
    garfieldThread.join();
}


int main() {
    int capacity = 20;

  initscr();            // Start curses mode
      curs_set(0);          // Hide the cursor
    refresh();            // Print it on to the real screen
    // Get the screen dimensions
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create the main window (full screen)

    int margin = 1;

    // // Calculate dimensions for the sub-windows
  int left_width = xMax * 3 / 4 ;
    int right_width = xMax - left_width ;
    int upper_height = yMax * 3 / 5 ;
    int lower_height = yMax - upper_height ;


    // // Create the left upper window
    WINDOW *leftwin = newwin(upper_height , left_width, 0, 0);
    box(leftwin, 0, 0);
 mvwprintw(leftwin, 1, 1, "This is the left upper window.");
    wrefresh(leftwin);


    // // Create the right upper window
   WINDOW *rightwin = newwin(upper_height, right_width, 0, left_width );
    box(rightwin, 0, 0);
    wrefresh(rightwin);


    // // Create the lower window
    WINDOW *lowerwin = newwin(lower_height, xMax, upper_height, 0);
    box(lowerwin, 0, 0);
    wrefresh(lowerwin);

    // Wait for user input to exit
    getch();
    
    // Clean up
    delwin(leftwin);
    delwin(rightwin);
    delwin(lowerwin);
    endwin();          

    // char choice;
    // do {
    //     std::cout << "\nMenu:\n";
    //     std::cout << "1. Rozpocznij symulację\n";
    //     std::cout << "2. Ustaw pojemność lodówki (" << capacity << ")\n";
    //     std::cout << "3. Wyjście\n";
    //     std::cout << "Wybierz opcję: ";
    //     std::cin >> choice;

    //     switch (choice) {
    //         case '1':
    //             startSimulation(capacity);
    //             break;
    //         case '2':
    //             std::cout << "Podaj pojemność lodówki: ";
    //             std::cin >> capacity;
    //             break;
    //         case '3':
    //             std::cout << "Zamykanie programu...\n";
    //             break; 
    //         default:
    //             std::cout << "Nieprawidłowa opcja. Spróbuj ponownie.\n";
    //     }
    // } while (choice != '4');

    return 0;
}