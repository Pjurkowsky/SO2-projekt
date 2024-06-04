#include "fridge.h"

Fridge::Fridge(int capacity) : m_capacity(capacity), m_lasagnas(0)
{
}

void Fridge::addLasagna()
{
    m_lasagnas++;
}

void Fridge::takeLasagna()
{
    m_lasagnas--;
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