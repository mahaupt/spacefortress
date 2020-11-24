#pragma once

#include <ncurses.h>

#include "../../tools/console.hpp"
#include "../../ui/window.hpp"
#include "../ship.hpp"

namespace shipos {
enum class ProgramState {
  RUN,   // running
  HALT,  // halted
  TERM   // terminated
};

class Program {
 public:
  Program(Ship* ship);
  Program(Ship* ship, WindowAlignment alignment_x, WindowAlignment alignment_y,
          double size_x, double size_y);
  virtual ~Program();
  virtual void render(ConsoleKey key);
  ProgramState getState() { return this->state; }
  virtual void setState(ProgramState s) { this->state = s; }
  virtual void setWinState(WindowState state);
  WINDOW* getWin() { return this->win; }

 protected:
  WINDOW* win;
  Window* window;
  Ship* ship;
  ProgramState state;
  bool is_main_window;
};
}  // namespace shipos
