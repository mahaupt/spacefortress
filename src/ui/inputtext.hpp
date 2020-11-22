#pragma once
#include <cmath>
#include <string>

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
  }
  void afterFocus() {
    this->selected = false;
    curs_set(0);
  }

 private:
  std::string label;
  std::string value;

  bool selected;
  int cursor_pos;
  int width;

  void processInput(ConsoleKey key);
  using UiElement::calcDrawOffset;
};
