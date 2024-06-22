#include "doe.h"

Doe::Doe(Fridge &fridge, Clock &clock, std::mutex &mutex, std::condition_variable &cv, Window *windows) : m_fridge(fridge), m_mutex(mutex), m_cv(cv), m_windows(windows), m_clock(clock)
{
}

void Doe::exists()
{
    while (true)
    {
        if (m_clock.getHours() >= 3 && m_clock.getHours() < 12)
                eatLasagna();
    
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void Doe::eatLasagna()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this]
              { return m_fridge.getLasagnasCount() > 0; });

    m_fridge.takeLasagna();

    m_windows[2].print("Doe ate lasagna. Remaining: " + std::to_string(m_fridge.getLasagnasCount()), 1, m_windows[2].getCursorY() + 1, 1);
    m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);

    m_cv.notify_one();
}


