#pragma once
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
  void beforeFocus() {
    this->selected = true;
    curs_set(1);
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

  void processInput(ConsoleKey key);
  using UiElement::calcDrawOffset;
};
