#include "garfield.h"

Garfield::Garfield(Fridge& fridge, std::mutex& mutex, std::condition_variable& cv) 
    : m_fridge(fridge), m_mutex(mutex), m_cv(cv)
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
    m_cv.wait(lock, [this] { return m_fridge.getLasagnasCount() > 0;});
    m_fridge.takeLasagna();
    
    std::cout << "Garfield ate lasagna. Remaining: " << m_fridge.getLasagnasCount() << "\n";

    m_cv.notify_one();
}
