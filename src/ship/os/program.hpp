#pragma once

#include <ncurses.h>

#include "../../tools/console.hpp"
#include "../ship.hpp"

namespace shipos {
enum class ProgramState {
  RUN,   // running
  HALT,  // halted
  TERM   // terminated
};

class Program {
 public:
  Program(WINDOW* win, Ship* ship);
  virtual ~Program() {}
  virtual void render(ConsoleKey key) {}
  ProgramState getState() { return this->state; }
  virtual void setState(ProgramState s) { this->state = s; }
  WINDOW* getWin() { return this->win; }

 protected:
  WINDOW* win;
  Ship* ship;
  ProgramState state;
};
}  // namespace shipos
