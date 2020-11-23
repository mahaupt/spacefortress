#pragma once

#include <ncurses.h>

#include "../../tools/console.hpp"
#include "../ship.hpp"

namespace shipos {
class Program {
 public:
  Program(WINDOW* win, Ship* ship);
  virtual ~Program() {}
  virtual void render(ConsoleKey key) {}

 protected:
  WINDOW* win;
  Ship* ship;
};
}  // namespace shipos
