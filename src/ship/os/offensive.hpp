#pragma once

#include "../modules/sensor.hpp"
#include "program.hpp"

namespace shipos {
class Offensive : public Program {
 public:
  Offensive(Ship* ship);
  Offensive(Ship* ship, WindowAlignment alignment_x,
            WindowAlignment alignment_y, double size_x, double size_y);

 private:
  int selection;
  module::Sensor* psensor;

  void render(ConsoleKey key);
};
}  // namespace shipos