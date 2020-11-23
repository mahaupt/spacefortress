#include "terminal.hpp"

shipos::Terminal::Terminal(WINDOW* win, Ship* ship)
    : Program(win, ship), input_field(0, 0, "") {
  terminal_lines.push_back("ShipOs Terminal");
  input_field.setWin(win);
  input_field.setPosition(0, 0, TOP, LEFT);
  input_field.setFiller("");
  input_field.setSelected(true);

  // activate right away
  Console::showCursor(true);
}

void shipos::Terminal::render(ConsoleKey key) {
  size_t i;
  for (i = 0; i < this->terminal_lines.size(); i++) {
    mvwprintw(this->win, 1 + i, 1, this->terminal_lines[i].c_str());
  }

  // clear and reprint text field
  wmove(this->win, 1 + i, 0);
  wclrtoeol(this->win);
  mvwprintw(this->win, 1 + i, 1, "$ ");
  input_field.setPosition(3, i + 1);
  input_field.render(key);
}

void shipos::Terminal::setState(ProgramState s) {
  this->state = s;
  if (s == shipos::ProgramState::RUN) {
    input_field.setSelected(true);
    Console::showCursor(true);
  } else {
    input_field.setSelected(false);
    Console::showCursor(false);
  }
}
