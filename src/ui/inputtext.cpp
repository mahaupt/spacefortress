#include "inputtext.hpp"

InputText::InputText() : cursor_pos(0), width(20) {}

void InputText::render(ConsoleKey key) {
  this->processInput(key);
  int start_x = round(COLS / 2.0f - this->width / 2.0f);
  int start_y = LINES - 1;

  std::string output = value;
  while (output.length() < this->width) {
    output += "_";
  }

  mvprintw(start_y, start_x, output.c_str());
}

void InputText::processInput(ConsoleKey key) {
  if (key < 0) return;

  if (key >= 'a' && key <= 'z') {
    this->value += key;
  }
  if (key >= 'A' && key <= 'Z') {
    this->value += key;
  }
}
