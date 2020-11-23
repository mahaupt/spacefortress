#pragma once

#include <ncurses.h>

#include "../tools/console.hpp"

class Window {
 public:
  Window();
  ~Window();

  void render(ConsoleKey key);

 private:
  WINDOW* win;
};
