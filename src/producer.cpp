#include "producer.h"

int Producer::number_of_producers = 0;

Producer::Producer(Fridge &fridge, std::mutex& mutex, std::condition_variable &cv) : m_fridge(fridge), m_mutex(mutex), m_cv(cv)
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

    m_fridge.addLasagna();

    std::cout << "Producer " << m_id << " added lasagna. Total: " << m_fridge.getLasagnasCount() << "\n";


    m_cv.notify_one();
}
