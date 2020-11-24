#pragma once

#include <cmath>

#include "program.hpp"

namespace shipos {
class Map : public Program {
 public:
  Map(WINDOW* win, Ship* ship);
  void render(ConsoleKey key);

 private:
  int wwidth;
  int wheight;

  void getWindowSize();
};
}  // namespace shipos
