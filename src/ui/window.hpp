#pragma once

#include <ncurses.h>

#include <cmath>

#include "../tools/console.hpp"

enum class WindowAlignment { LEFT, RIGHT };

class Window {
 public:
  Window(WindowAlignment alignment, double size);
  ~Window();

  void render(ConsoleKey key);
  void setTitle(std::string title) { this->window_title = title; }
  void setBorder(bool border) { this->window_border = border; }
  WINDOW *getWin() { return this->win; }

 private:
  WINDOW *win;
  WindowAlignment alignment;
  double size;
  bool window_border;
  std::string window_title;

  int x;
  int y;
  int width;
  int height;
  int cols_save;
  int lines_save;

  void calcWindowSize(int &x, int &y, int &width, int &height);
  void resizeWindow();
};
