#pragma once

#include <curses.h>

#include <cmath>

#include "../tools/console.hpp"

enum class WindowAlignment { LEFT, RIGHT, MIDDLE, TOP, BOTTOM };
enum class WindowState { VISIBLE, HIDDEN };

class Window {
 public:
  Window(WindowAlignment alignment_x, WindowAlignment alignment_y,
         double size_x, double size_y);
  ~Window();

  void render(ConsoleKey key);
  void setTitle(const std::string &title) { this->window_title = title; }
  void setBorder(bool border) { this->window_border = border; }
  void setState(WindowState s) { this->state = s; }
  WindowState getState() { return this->state; }
  WINDOW *getWin() { return this->win; }

 private:
  WINDOW *win;
  WindowAlignment alignment_x;
  WindowAlignment alignment_y;
  WindowState state;
  double size_x;
  double size_y;
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
