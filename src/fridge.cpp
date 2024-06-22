#include "fridge.h"

Fridge::Fridge(int capacity, Window* windows) : m_capacity(capacity), m_lasagnas(0), m_windows(windows)
{
    drawFridge();

}

void Fridge::addLasagna()
{
    m_lasagnas++;
    drawLasagnas();
    m_windows[1].print("s:" + std::to_string(m_capacity), 9, 0);
    m_windows[1].print("c:" + std::to_string(m_lasagnas), 14, 0);
}

void Fridge::takeLasagna()
{
    m_lasagnas--;
    drawLasagnas();
    m_windows[1].print("s:" + std::to_string(m_capacity), 9, 0);
    m_windows[1].print("c:" + std::to_string(m_lasagnas), 14, 0);

}

int Fridge::getLasagnasCount() const
{
    return m_lasagnas;
}

bool Fridge::isUsed() const
{
    return m_isUsed;
}

bool Fridge::isFull() const
{
    return m_lasagnas == m_capacity;
}

bool Fridge::isEmpty() const
{
    return m_lasagnas == 0;
}

void Fridge::setUsed(bool used)
{
    m_isUsed = used;
}

void Fridge::setCapacity(int capacity)
{
    m_capacity = capacity;
    m_windows[1].print("s:" + std::to_string(m_capacity), 9, 0);
    drawLasagnas();
}

int Fridge::getCapacity()
{
    return m_capacity;
}

void Fridge::drawFridge()
{
    // corners
    mvwaddch(m_windows[1].getWindow(), 2, 2, ACS_ULCORNER);
    mvwaddch(m_windows[1].getWindow(), 2, 19, ACS_URCORNER);

    mvwaddch(m_windows[1].getWindow(), 18, 2, ACS_LLCORNER);
    mvwaddch(m_windows[1].getWindow(), 18, 19, ACS_LRCORNER);  
   
    // sides
    mvwvline(m_windows[1].getWindow(), 3, 2, ACS_VLINE, 15); 
    mvwvline(m_windows[1].getWindow(), 3, 19, ACS_VLINE, 15); 

    // top
    wmove(m_windows[1].getWindow(),2,3);
    whline(m_windows[1].getWindow(), ACS_HLINE, 16);
    for (int i = 0; i < m_numberOfShelves; i++) //  shelves
    {
        wmove(m_windows[1].getWindow(), 4 + i * 2, 3);
        whline(m_windows[1].getWindow(), ACS_HLINE, 16);
    }
    // bottom
    wmove(m_windows[1].getWindow(), 18,3);
    whline(m_windows[1].getWindow(), ACS_HLINE, 16);

}

void Fridge::drawLasagnas()
{
    m_windows[1].clear();
    drawFridge();
    for (int i = 0; i < m_lasagnas; i++)
        m_windows[1].print("L", 3 + (i % 8) * 2, 3 + (i / 8) * 2);
}