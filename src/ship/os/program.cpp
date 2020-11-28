#include "program.hpp"

using namespace shipos;
/**
 * Constructor for using the main window
 * @param ship [description]
 */
Program::Program(Ship* ship)
    : win(stdscr), window(0), ship(ship), state(ProgramState::RUN) {}

/**
 * Constructor for using a self created window
 * @param ship        [description]
 * @param alignment_x [description]
 * @param alignment_y [description]
 * @param size_x      [description]
 * @param size_y      [description]
 */
Program::Program(Ship* ship, WindowAlignment alignment_x,
                 WindowAlignment alignment_y, double size_x, double size_y)
    : ship(ship), state(ProgramState::RUN) {
  this->window = new Window(alignment_x, alignment_y, size_x, size_y);
  this->win = this->window->getWin();
}

Program::~Program() {
  if (this->window != 0) {
    delete this->window;
    this->window = 0;
  }
}

void Program::render(ConsoleKey key) {
  if (this->window != 0) {
    this->window->render(key);
  }
}

void Program::setWinState(WindowState state) {
  if (this->window == 0) return;
  this->window->setState(state);
}

void Program::getWindowSize() {
  getmaxyx(this->win, this->wheight, this->wwidth);
}

void Program::showError(const int& y, const std::string& error) {
  this->showCentered(y, error, A_BOLD | A_BLINK);
}

void Program::showCentered(const int& y, const std::string& msg,
                           const int& attr) {
  int errorx = round((this->wwidth - msg.length()) / 2.0);
  wattron(this->win, attr);
  mvwprintw(this->win, y, errorx, msg.c_str());
  wattroff(this->win, attr);
}
