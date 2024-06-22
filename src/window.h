#pragma once

#include <iostream>
#include <ncurses.h>

class Window {
public:
    Window(int width, int height, int x, int y, const std::string& name);
    ~Window();
    void print(const std::string& text, int x, int y, int color = 0);
    void printAsciiArt( const char *art[], int rows,  int y, int x);
    void clear();
    void refresh();
    WINDOW* getWindow();
    void setCursorPos(int x, int y);
    int getCursorX();
    int getCursorY();
private:
    WINDOW* m_window;

    int m_width;
    int m_height;
    const std::string m_name;

    int m_cursorX = 0;
    int m_cursorY = 0;
};
