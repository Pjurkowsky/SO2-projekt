#include "producer.h"

int Producer::number_of_producers = 0;

Producer::Producer(Fridge &fridge, Clock &clock, std::mutex& mutex, std::condition_variable &cv, Window* windows) 
: m_fridge(fridge), m_mutex(mutex), m_cv(cv), m_windows(windows), m_clock(clock)
{
    number_of_producers++;
    m_id = number_of_producers;
}

void Producer::produce()
{
    while (true)
    {
        addLasagna();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Producer::addLasagna()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this] { return !m_fridge.isFull(); });

    if (m_clock.getHours() >= 18 || m_clock.getHours() < 6)
    {
        if(m_isWorking == true)
        {
            m_windows[2].print("Delivery man " + std::to_string(m_id) + " went to home.", 1, m_windows[2].getCursorY() + 1, 2);
            m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);
            m_isWorking = false;
        }

        m_cv.notify_one();
        return;
    }

    if(m_isWorking == false)
    {
        m_windows[2].print("Delivery man " + std::to_string(m_id) + " started work.", 1, m_windows[2].getCursorY() + 1, 2);
        m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);
        m_isWorking = true;
    }


    m_fridge.addLasagna();

    m_windows[2].print("Delivery man " + std::to_string(m_id) + " added lasagna. Total: " + std::to_string(m_fridge.getLasagnasCount()), 1, m_windows[2].getCursorY() + 1, 2);
    m_windows[2].setCursorPos(m_windows[2].getCursorX(), m_windows[2].getCursorY() + 1);
    m_cv.notify_one();
}
