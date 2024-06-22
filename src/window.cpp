#include "window.h"

Window::Window(int width, int height, int x, int y, const std::string& name) : m_window(newwin(height, width, y, x)), m_width(width), m_height(height), m_name(name)
{
    box(m_window, 0, 0);
    print(name, 2, 0);
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
}

Window::~Window()
{
    delwin(m_window);
}

void Window::print(const std::string &text, int x, int y, int color)
{
    wattron(m_window, COLOR_PAIR(color));
    mvwprintw(m_window, y, x, text.c_str());
    wattroff(m_window, COLOR_PAIR(color));
    wrefresh(m_window);
}

void Window::clear()
{
    wclear(m_window);
    box(m_window, 0, 0);
    print(m_name, 2, 0);
}

void Window::refresh()
{
}

WINDOW* Window::getWindow()
{
    return m_window;
}

void Window::setCursorPos(int x, int y)
{
    m_cursorX = x;
    m_cursorY = y;
    
    if (m_cursorX >= m_width || m_cursorY >= m_height - 1)
    {
        clear();
        wmove(m_window, 0, 0);
        m_cursorX = 0;
        m_cursorY = 0;
    }

}

int Window::getCursorX()
{
    return m_cursorX;
}

int Window::getCursorY()
{
    return m_cursorY;
}

void Window::printAsciiArt(const char *art[], int rows, int y, int x) {
    for (int i = 0; i < rows; ++i) {
        mvwprintw(m_window, y + i, x, art[i]);
    }
}