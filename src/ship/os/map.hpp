#pragma once

#include <cmath>

#include "program.hpp"

namespace shipos {
class Map : public Program {
 public:
  Map(Ship* ship);
  Map(Ship* ship, WindowAlignment alignment_x, WindowAlignment alignment_y,
      double size_x, double size_y);
  void render(ConsoleKey key);

 private:
  int wwidth;
  int wheight;

  void getWindowSize();
};
}  // namespace shipos
