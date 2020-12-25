#include "uielement.hpp"

UiElement::UiElement(int x, int y, UiAlignment align_x, UiAlignment align_y)
    : win(stdscr), x(x), y(y), align_x(align_x), align_y(align_y) {}

void UiElement::setPosition(int x, int y, UiAlignment align_x,
                            UiAlignment align_y) {
  this->x = x;
  this->y = y;
  this->align_x = align_x;
  this->align_y = align_y;
}

void UiElement::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

void UiElement::calcDrawOffset(int& dx, int& dy) {
  // calculate anchor x pos
  dx = this->x;
  switch (this->align_x) {
    case (MIDDLE):
      dx = (int)round(COLS / 2.0f) + this->x;
      break;
    case (RIGHT):
      dx = COLS;
      break;
    default:
      // nothing
      break;
  }

  // calculate anchor y pos
  dy = this->y;
  switch (this->align_y) {
    case (MIDDLE):
      dy = (int)round(LINES / 2.0f) + this->y;
      break;
    case (BOTTOM):
      dy = LINES + this->y;
      break;
    default:
      // nothing
      break;
  }
}
