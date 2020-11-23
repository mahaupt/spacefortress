#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>

#include "../tools/console.hpp"
#include "../tools/log.hpp"
#include "uielement.hpp"

/**
 * [render description]
 */
class InputText : public UiElement {
 public:
  InputText(int x, int y, std::string label);
  void render(ConsoleKey key);
  void setFiller(std::string f) { this->filler = f; }
  void setSelected(bool s) { this->selected = s; }
  std::string getValue() { return this->value; }
  void setValue(std::string s);
  void beforeFocus() {
    this->selected = true;
    Console::showCursor(true);
  }
  void afterFocus() {
    this->selected = false;
    Console::showCursor(false);
  }

 private:
  bool selected;
  int cursor_pos;
  size_t width;

  std::string label;
  std::string value;
  std::string filler;

  void processInput(ConsoleKey key);
  using UiElement::calcDrawOffset;
};
