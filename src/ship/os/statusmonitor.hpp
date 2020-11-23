#pragma once

#include "../../tools/console.hpp"
#include "program.hpp"

namespace shipos {
class StatusMonitor : public Program {
 public:
  StatusMonitor(WINDOW* win, Ship* ship);
  void render(ConsoleKey key);

 private:
};
}  // namespace shipos
