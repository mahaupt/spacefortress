#include "window.hpp"

Window::Window(WindowAlignment alignment_x, WindowAlignment alignment_y,
               double size_x, double size_y)
    : win(0),
      alignment_x(alignment_x),
      alignment_y(alignment_y),
      state(WindowState::VISIBLE),
      size_x(size_x),
      size_y(size_y) {
  this->calcWindowSize(this->x, this->y, this->width, this->height);
  this->win = newwin(this->height, this->width, this->y, this->x);
  this->cols_save = COLS;
  this->lines_save = LINES;

  this->window_border = true;
}

Window::~Window() {
  if (this->win != 0) {
    delwin(this->win);
  }
}

/**
 * renders and refreshes the window, call this function after you drawn on the
 * window
 *
 * @param key Console key
 */
void Window::render(ConsoleKey key) {
  if (this->window_border) {
    box(this->win, 0, 0);
  }
  if (this->window_title.length() > 0) {
    size_t start_x =
        round(this->width / 2.0f - this->window_title.length() / 2.0f);
    mvwprintw(this->win, 0, start_x, this->window_title.c_str());
  }

  wrefresh(this->win);
  this->resizeWindow();
}

/**
 * calculates the should-size of the window depending on
 * the size of the main window and the window alignment
 * used for repositioning and rescaling purposes
 */
void Window::calcWindowSize(int &x, int &y, int &width, int &height) {
  x = 0;
  y = 0;

  width = round(COLS * this->size_x);
  height = round(LINES * this->size_y);

  if (this->alignment_x == WindowAlignment::RIGHT) {
    x = COLS - width;
  }
  if (this->alignment_y == WindowAlignment::BOTTOM) {
    y = LINES - height;
  }
}

/**
 * resizes Window if console window changed
 */
void Window::resizeWindow() {
  if (this->cols_save == COLS && this->lines_save == LINES) return;

  this->calcWindowSize(this->x, this->y, this->width, this->height);
  wresize(this->win, this->height, this->width);
  mvwin(this->win, this->y, this->x);
  this->cols_save = COLS;
  this->lines_save = LINES;
  werase(this->win);
  erase();
}
