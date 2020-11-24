#pragma once
#include "program.hpp"

namespace shipos {
class Helm : public Program {
 public:
  Helm(WINDOW* win, Ship* ship);
  void render(ConsoleKey key);

 private:
};
}  // namespace shipos
