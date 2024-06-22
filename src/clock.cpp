#include "clock.h"

Clock::Clock(Window* windows): m_windows(windows) {}

void Clock::drawClock() {
    std::string hours = std::to_string(m_hours);
    std::string minutes = std::to_string(m_minutes);
    std::string seconds = std::to_string(m_seconds);

    if (m_hours < 10) {
        hours = "0" + hours;
    }
    if (m_minutes < 10) {
        minutes = "0" + minutes;
    }
    if (m_seconds < 10) {
        seconds = "0" + seconds;
    }

    mvwvline(m_windows[0].getWindow(), 3, 25, ACS_VLINE, 1); 
    mvwvline(m_windows[0].getWindow(), 3, 34, ACS_VLINE, 1); 
  

    mvwaddch(m_windows[0].getWindow(), 2, 25, ACS_ULCORNER);
    mvwaddch(m_windows[0].getWindow(), 2, 34, ACS_URCORNER);

    mvwaddch(m_windows[0].getWindow(), 4, 25, ACS_LLCORNER);
    mvwaddch(m_windows[0].getWindow(), 4, 34, ACS_LRCORNER);  


    wmove(m_windows[0].getWindow(), 2,26);
    whline(m_windows[0].getWindow(), ACS_HLINE, 8);
    wmove(m_windows[0].getWindow(), 4,26);
    whline(m_windows[0].getWindow(), ACS_HLINE, 8);

    m_windows[0].print(hours + ":" + minutes + ":" + seconds, 26, 3, 1);

    m_hours++;

    if (m_hours == 24) {
        m_hours = 0;
    }
}

void Clock::run() {
    while (true) {
        drawClock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int Clock::getHours() const {
    return m_hours;
}