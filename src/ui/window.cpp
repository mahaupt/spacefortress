#include "window.hpp"

Window::Window() : win(0) { this->win = newwin(5, 10, 10, 30); }

Window::~Window() {
  if (this->win != 0) {
    delwin(this->win);
  }
}

void Window::render(ConsoleKey key) {
  box(this->win, 0, 0);

  wrefresh(this->win);
}
