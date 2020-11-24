#pragma once

#include "../../tools/console.hpp"
#include "program.hpp"

namespace shipos {
class StatusMonitor : public Program {
 public:
  StatusMonitor(Ship* ship);
  StatusMonitor(Ship* ship, WindowAlignment alignment_x,
                WindowAlignment alignment_y, double size_x, double size_y);
  void render(ConsoleKey key);

 private:
};
}  // namespace shipos
