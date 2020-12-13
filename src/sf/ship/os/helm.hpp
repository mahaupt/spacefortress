#pragma once
#include <curses.h>

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
  bool autopilot;
  double engpwr;

  module::Engine* ptr_engine;

  void setThrust(const Vec2& thr);
};
}  // namespace shipos
