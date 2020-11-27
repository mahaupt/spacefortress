#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>
#include <vector>

#include "uielement.hpp"

/**
 * Class to display text or banners of text on screen
 */
class Text : public UiElement {
 public:
  Text(int x, int y, UiAlignment align_x, UiAlignment align_y,
       UiAlignment align_text);
  using UiElement::setPosition;
  void setPosition(int x, int y, UiAlignment align_x, UiAlignment align_y,
                   UiAlignment align_text);
  void addTextLine(const std::string& line);
  void render(ConsoleKey key);

 private:
  std::vector<std::string> textlines;
  UiAlignment align_text;
  int text_size;

  using UiElement::calcDrawOffset;
};
