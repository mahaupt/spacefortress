#pragma once
#include <list>
#include <memory>

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
  int selection;

  module::Sensor* psensor;
};
}  // namespace shipos
