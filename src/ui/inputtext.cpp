#include "inputtext.hpp"

InputText::InputText(int x, int y, std::string label)
    : UiElement(x, y, MIDDLE, MIDDLE),
      cursor_pos(0),
      selected(false),
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
  if (key < 0) return;

  // add chars
  if (this->value.length() < this->width) {
    // - . _ : SP
    if (key >= 45 && key <= 46 || key >= 48 && key <= 57 || key == 58 ||
        key == 95 || key == 32) {
      this->value += key;
      this->cursor_pos++;
    }
    // A - z
    if (key >= 65 && key <= 90 || key >= 97 && key <= 122) {
      this->value += key;
      this->cursor_pos++;
    }
  }

  // delete characters
  if (this->value.length() > 0) {
    if (key == BACKSPACE && this->cursor_pos > 0) {
      this->value = this->value.substr(0, this->cursor_pos - 1) +
                    this->value.substr(this->cursor_pos);
      this->cursor_pos--;
    }
    if (key == DELETE && this->cursor_pos < this->value.length()) {
      this->value = this->value.substr(0, this->cursor_pos) +
                    this->value.substr(this->cursor_pos + 1);
    }
  }

  if (key == ARROW_LEFT) {
    this->cursor_pos--;
    if (this->cursor_pos < 0) {
      this->cursor_pos = 0;
    }
  }
  if (key == ARROW_RIGHT) {
    this->cursor_pos++;
    if (this->cursor_pos > this->value.length()) {
      this->cursor_pos = this->value.length();
    }
  }

  Log::debug("key: " + std::to_string(key));
}
