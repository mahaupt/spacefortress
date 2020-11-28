#pragma once
#include <list>

#include "../modules/sensor.hpp"
#include "program.hpp"

namespace shipos {
class Sensor : public Program {
 public:
  Sensor(Ship* ship);
  Sensor(Ship* ship, WindowAlignment alignment_x, WindowAlignment alignment_y,
         double size_x, double size_y);

  void render(ConsoleKey key);

 private:
  int wwidth;
  int wheight;
  int selection;

  module::Sensor* psensor;

  void getWindowSize();
};
}  // namespace shipos