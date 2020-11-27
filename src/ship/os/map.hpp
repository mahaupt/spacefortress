#pragma once

#include <cmath>
#include <vector>

#include "../../gameobject.hpp"
#include "../../tools/lang.hpp"
#include "../../tools/vec2.hpp"
#include "../modules/sensor.hpp"
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
  int zoom;
  module::Sensor* ptr_sensor;

  void findShipSensor();
  void getWindowSize();
};
}  // namespace shipos
