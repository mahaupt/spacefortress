#include "program.hpp"

/**
 * Constructor for using the main window
 * @param ship [description]
 */
shipos::Program::Program(Ship* ship)
    : win(stdscr), window(0), ship(ship), state(ProgramState::RUN) {}

/**
 * Constructor for using a self created window
 * @param ship        [description]
 * @param alignment_x [description]
 * @param alignment_y [description]
 * @param size_x      [description]
 * @param size_y      [description]
 */
shipos::Program::Program(Ship* ship, WindowAlignment alignment_x,
                         WindowAlignment alignment_y, double size_x,
                         double size_y)
    : ship(ship), state(ProgramState::RUN) {
  this->window = new Window(alignment_x, alignment_y, size_x, size_y);
  this->win = this->window->getWin();
}

shipos::Program::~Program() {
  if (this->window != 0) {
    delete this->window;
    this->window = 0;
  }
}

void shipos::Program::render(ConsoleKey key) {
  if (this->window != 0) {
    this->window->render(key);
  }
}

void shipos::Program::setWinState(WindowState state) {
  if (this->window == 0) return;
  this->window->setState(state);
}
