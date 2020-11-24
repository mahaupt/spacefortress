#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>

#include "../../tools/console.hpp"
#include "../ship.hpp"
#include "program.hpp"

namespace shipos {
class Helm : public Program {
 public:
  Helm(WINDOW* win, Ship* ship);
  void render(ConsoleKey key);

 private:
  double rot;
  int wwidth;
  int wheight;

  void getWindowSize();
};
}  // namespace shipos
