#pragma once
#include <string>

#include "uielement.hpp"

class MenuItem : public UiElement {
 public:
  MenuItem(int x, int y, std::string text, void (*cb)(void));
  void render(ConsoleKey key);

  void beforeFocus() { this->selected = true; }
  void afterFocus() { this->selected = false; }
  void onSelection() {
    if (callback != 0) {
      callback();
    }
  }

 private:
  bool selected;
  std::string text;
  void (*callback)(void);

  using UiElement::calcDrawOffset;
};
