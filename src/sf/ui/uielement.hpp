#pragma once
#include <curses.h>

#include <cmath>

#include "../tools/console.hpp"

enum UiAlignment { TOP, MIDDLE, BOTTOM, LEFT, RIGHT };

class UiElement {
 public:
  UiElement(int x, int y, UiAlignment align_x, UiAlignment align_y);

  void setPosition(int x, int y);
  void setPosition(int x, int y, UiAlignment align_x, UiAlignment align_y);

  void setWin(WINDOW* w) { this->win = w; }
  WINDOW* getWin() { return this->win; }

  // render function
  virtual void render(ConsoleKey key){};

  // will be called when element gets cursor focus
  virtual void beforeFocus(){};

  // will be called when element gets focus removed
  virtual void afterFocus(){};

  // will be called when a selection on element is made
  virtual void onSelection(){};

 protected:
  WINDOW* win;
  int x, y;
  UiAlignment align_x;
  UiAlignment align_y;

  void calcDrawOffset(int& dx, int& dy);
};
