#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>
#include <vector>

enum DisplayAlignment { TOP, MIDDLE, BOTTOM, LEFT, RIGHT };

/**
 * Class to display text or banners of text on screen
 */
class Text {
 public:
  Text(int x, int y, DisplayAlignment align_x, DisplayAlignment align_y,
       DisplayAlignment align_text);
  void setPosition(int x, int y, DisplayAlignment align_x,
                   DisplayAlignment align_y, DisplayAlignment align_text);
  void addTextLine(std::string line);
  void render();

 private:
  std::vector<std::string> textlines;
  DisplayAlignment align_x;
  DisplayAlignment align_y;
  DisplayAlignment align_text;
  int x, y;
  int text_size;
};
