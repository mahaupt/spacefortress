#pragma once

#include <ncurses.h>

#include <cmath>

#include "../tools/console.hpp"

enum class WindowAlignment { LEFT, RIGHT };
enum class WindowState { VISIBLE, HIDDEN };

class Window {
 public:
  Window(WindowAlignment alignment, double size);
  ~Window();

  void render(ConsoleKey key);
  void setTitle(std::string title) { this->window_title = title; }
  void setBorder(bool border) { this->window_border = border; }
  void setState(WindowState s) { this->state = s; }
  WindowState getState() { return this->state; }
  WINDOW *getWin() { return this->win; }

 private:
  WINDOW *win;
  WindowAlignment alignment;
  WindowState state;
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
