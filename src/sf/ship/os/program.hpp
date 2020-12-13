#pragma once

#include <curses.h>

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
  Program(Ship* ship, const std::string& type);
  Program(Ship* ship, const std::string& type, WindowAlignment alignment_x,
          WindowAlignment alignment_y, double size_x, double size_y);
  virtual ~Program();

  virtual void render(ConsoleKey key);

  ProgramState getState() { return this->state; }
  std::string getType() { return this->type; }
  virtual void setState(ProgramState s) { this->state = s; }
  virtual void setWinState(WindowState state);
  WINDOW* getWin() { return this->win; }

 protected:
  WINDOW* win;
  Window* window;
  Ship* ship;
  std::string type;
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
