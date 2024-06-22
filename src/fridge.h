#pragma once

#include <iostream>
#include "window.h"


class Fridge {
public:
    Fridge(int capacity, Window* windows);
    
    void addLasagna();
    void takeLasagna();

    int getLasagnasCount() const;

    bool isFull() const;
    bool isEmpty() const;

    bool isUsed() const;
    void setUsed(bool used);

    void setCapacity(int capacity);
    int getCapacity();

private:
    int m_capacity;
    int m_lasagnas;
    bool m_isUsed = false;
    Window* m_windows;

    const int m_lasagnasOnShelf = 8;
    const int m_numberOfShelves = 8;

    void drawFridge();
    void drawLasagnas();

};