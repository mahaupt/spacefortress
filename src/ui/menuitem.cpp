#include "menuitem.hpp"

MenuItem::MenuItem(int x, int y, std::string text, void (*cb)(void))
    : UiElement(x, y, MIDDLE, MIDDLE),
      text(text),
      selected(false),
      callback(cb) {}

void MenuItem::render(ConsoleKey key) {
  int start_x, start_y;
  this->calcDrawOffset(start_x, start_y);

  if (this->selected) {
    attrset(A_BOLD);
  }

  int dx = floor(this->text.length() / 2.0f);
  mvprintw(start_y, start_x - dx, this->text.c_str());

  if (this->selected) {
    attrset(A_NORMAL);
  }
}
