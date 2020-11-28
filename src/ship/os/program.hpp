#pragma once

#include <ncurses.h>

//#include <string>

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

  int wwidth;
  int wheight;

  void getWindowSize();
  void showError(const int& y, const std::string& error);
  void showCentered(const int& y, const std::string& msg,
                    const int& attr = A_NORMAL);
};
}  // namespace shipos
