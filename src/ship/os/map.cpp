#include "map.hpp"

shipos::Map::Map(Ship* ship) : Program(ship) {}

shipos::Map::Map(Ship* ship, WindowAlignment alignment_x,
                 WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y) {
  this->window->setTitle("Map");
}

void shipos::Map::render(ConsoleKey key) {
  this->getWindowSize();

  werase(this->win);

  // get ship pos and center pos
  double sx;
  double sy;
  int cx = round(this->wwidth / 2.0);
  int cy = round(this->wheight / 2.0);
  this->ship->getPos(sx, sy);

  // draw objects
  for (int spx = 1; spx < this->wwidth - 2; spx++) {
    for (int spy = 1; spy < this->wheight - 2; spy++) {
      // calc game positions
      int gpx = round(sx) + spx - cx;
      int gpy = round(sy) - spy + cy;

      // test object at 3/3
      if (gpx == 3 && gpy == 3) {
        mvwprintw(this->win, spy, spx, ".");
      }

      // test object at -3/-3
      if (gpx == -3 && gpy == 3) {
        mvwprintw(this->win, spy, spx, "+");
      }
    }
  }

  // draw ship and pos info
  mvwprintw(this->win, cy, cx, "O");
  mvwprintw(this->win, 1, 2, "%.1f / %.1f", sx, sy);
  mvwprintw(this->win, this->wheight - 3, 1, "y");
  mvwprintw(this->win, this->wheight - 2, 2, "x");

  // render window
  Program::render(key);
}

/**
 * saves window dimensions
 * window class clears window for us if resized
 */
void shipos::Map::getWindowSize() {
  getmaxyx(this->win, this->wheight, this->wwidth);
}
