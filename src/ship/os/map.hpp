#pragma once

#include "program.hpp"

namespace shipos {
class Map : public Program {
 public:
  Map(WINDOW* win, Ship* ship);
  void render(ConsoleKey key);

 private:
};
}  // namespace shipos
