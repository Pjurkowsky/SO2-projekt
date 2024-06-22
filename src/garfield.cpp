#include "garfield.h"

Garfield::Garfield(Fridge &fridge, Clock &clock, std::mutex &mutex, std::condition_variable &cv, Window *windows)
    : m_fridge(fridge), m_mutex(mutex), m_cv(cv), m_windows(windows), m_clock(clock)
{
}

void Garfield::consume()
{
    while (true)
    {
        eatLasagna();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void Garfield::eatLasagna()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this]
              { return m_fridge.getLasagnasCount() > 0; });

    if (m_clock.getHours() >= 3 && m_clock.getHours() < 12)
    {
        if (m_isSleeping == false)
        {
            m_windows[2].print("Garfield went to sleep.", 1, m_windows[2].getCursorY() + 1, 1);
            m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);
            m_isSleeping = true;
        }
        m_cv.notify_one();
        return;
    }
    m_fridge.takeLasagna();
    if (m_isSleeping == true)
    {
        m_windows[2].print("Garfield woke up.", 1, m_windows[2].getCursorY() + 1, 1);
        m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);
        m_isSleeping = false;
    }

    m_windows[2].print("Garfield ate lasagna. Remaining: " + std::to_string(m_fridge.getLasagnasCount()), 1, m_windows[2].getCursorY() + 1, 1);
    m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);
    m_windows[0].printAsciiArt(customArt, 11, 1, 1);
    m_cv.notify_one();
}
