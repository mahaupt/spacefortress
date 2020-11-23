#pragma once
#include <curses.h>

#include "lang.hpp"
#include "log.hpp"

enum ConsoleKey {
  NONE = -1,
  ENTER = 10,
  ARROW_UP = 259,
  ARROW_DOWN = 258,
  ARROW_LEFT = 260,
  ARROW_RIGHT = 261,
  BACKSPACE = 263,
  DELETE = 330,
  KEY_Q = 113
};

/**
 * ncurses warpper
 */
class Console {
 public:
  Console();
  ~Console();

  void printBanner();

  // getch wrapper
  ConsoleKey getKey() { return (ConsoleKey)getch(); }

  static void sclear() { clear(); }
  static void srefresh() { refresh(); }
  static void setCursorPos(int x, int y);
  static void renderCursor();
  static void showCursor(bool show);

 private:
  bool show_cursor;
  int cursor_x;
  int cursor_y;
  static Console* self;
};
