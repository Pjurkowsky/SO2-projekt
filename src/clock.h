#pragma once

#include <iostream>
#include <thread>
#include "window.h"


class Clock {

public:
Clock(Window* windows);
void drawClock();

int getHours() const;

void run();

private:
Window* m_windows;
int m_hours = 12;
int m_minutes = 0;
int m_seconds = 0;
};