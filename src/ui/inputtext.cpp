#include "inputtext.hpp"

InputText::InputText() : cursor_pos(0), width(20), label("Username::") {}

void InputText::render(ConsoleKey key) {
  this->processInput(key);

  // calc start positions
  int start_x = round(COLS / 2.0f - this->width / 2.0f);
  int start_y = LINES - 1;
  start_x -= this->label.length();

  // format output str
  std::string output = value;
  while (output.length() < this->width) {
    output += "_";
  }
  output = this->label + output;

  // render
  mvprintw(start_y, start_x, output.c_str());
  curs_set(1);
  move(start_y, start_x + this->label.length() + this->cursor_pos);
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
