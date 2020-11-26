#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>

#include "../../tools/console.hpp"
#include "../../tools/lang.hpp"
#include "../modules/engine.hpp"
#include "../ship.hpp"
#include "program.hpp"

namespace shipos {
class Helm : public Program {
 public:
  Helm(Ship* ship);
  Helm(Ship* ship, WindowAlignment alignment_x, WindowAlignment alignment_y,
       double size_x, double size_y);
  void render(ConsoleKey key);

 private:
  double rot;
  int wwidth;
  int wheight;
  bool autopilot;
  double engpwr;

  Engine* ptr_engine;

  void getWindowSize();
  void findShipEngine();
  void setThrust(double x, double y);
};
}  // namespace shipos
