#pragma once
#include <curses.h>

enum ConsoleKey {
  NONE = -1,
  ENTER = 10,
  ARROW_UP = 259,
  ARROW_DOWN = 258,
  ARROW_LEFT = 260,
  ARROW_RIGHT = 261,
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

 private:
};
