#include "inputtext.hpp"

InputText::InputText(int x, int y, std::string label)
    : UiElement(x, y, MIDDLE, MIDDLE),
      selected(false),
      cursor_pos(0),
      width(20),
      label(label) {}

void InputText::render(ConsoleKey key) {
  // calc start positions
  int start_x, start_y;
  this->calcDrawOffset(start_x, start_y);
  start_x -= this->label.length();

  // interactions
  if (this->selected) {
    this->processInput(key);
    // move cursor
    Console::setCursorPos(start_y,
                          start_x + this->label.length() + this->cursor_pos);
  }

  // format output str
  std::string output = this->value;
  while (output.length() < this->width) {
    output += "_";
  }
  output = this->label + output;

  // render
  mvprintw(start_y, start_x, output.c_str());
}

void InputText::processInput(ConsoleKey key) {
  if (key == ConsoleKey::NONE) return;
  int ikey = (int)key;

  // add chars
  if (this->value.length() < this->width) {
    // - . _ : SP
    if (ikey >= 45 && ikey <= 46 || ikey >= 48 && ikey <= 57 || ikey == 58 ||
        ikey == 95 || ikey == 32) {
      this->value += ikey;
      this->cursor_pos++;
    }
    // A - z
    if (ikey >= 65 && ikey <= 90 || ikey >= 97 && ikey <= 122) {
      this->value += ikey;
      this->cursor_pos++;
    }
  }

  // delete characters
  if (this->value.length() > 0) {
    if (key == ConsoleKey::BACKSPACE && this->cursor_pos > 0) {
      this->value = this->value.substr(0, this->cursor_pos - 1) +
                    this->value.substr(this->cursor_pos);
      this->cursor_pos--;
    }
    if (key == ConsoleKey::DELETE && this->cursor_pos < this->value.length()) {
      this->value = this->value.substr(0, this->cursor_pos) +
                    this->value.substr(this->cursor_pos + 1);
    }
  }

  if (key == ConsoleKey::ARROW_LEFT) {
    this->cursor_pos--;
    if (this->cursor_pos < 0) {
      this->cursor_pos = 0;
    }
  }
  if (key == ConsoleKey::ARROW_RIGHT) {
    this->cursor_pos++;
    if (this->cursor_pos > this->value.length()) {
      this->cursor_pos = this->value.length();
    }
  }
}
