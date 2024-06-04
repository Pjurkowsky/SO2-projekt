#pragma once

#include <iostream>


class Fridge {
public:
    Fridge(int capacity);
    
    void addLasagna();
    void takeLasagna();

    int getLasagnasCount() const;
    bool isFull() const;
    bool isEmpty() const;

    bool isUsed() const;
    void setUsed(bool used);

private:
    int m_capacity;
    int m_lasagnas;
    bool m_isUsed = false;

};