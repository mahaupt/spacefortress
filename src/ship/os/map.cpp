#include "map.hpp"

shipos::Map::Map(Ship* ship, std::vector<GameObject*>* game_objects)
    : Program(ship), game_objects(game_objects) {}

shipos::Map::Map(Ship* ship, std::vector<GameObject*>* game_objects,
                 WindowAlignment alignment_x, WindowAlignment alignment_y,
                 double size_x, double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y),
      game_objects(game_objects) {
  this->window->setTitle(Lang::get("program_map"));
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
  for (size_t i = 0; i < this->game_objects->size(); i++) {
    // get position of object
    double gpx;
    double gpy;
    (*this->game_objects)[i]->getPos(gpx, gpy);

    // calc screen position
    double spx = cx + gpx - sx;
    double spy = cy - gpy + sy;

    // object is in map screen
    if (spx > 1 && spx < this->wwidth - 2 && spy > 1 &&
        spy < this->wheight - 2) {
      mvwprintw(this->win, round(spy), round(spx),
                (*this->game_objects)[i]->getSymbol().c_str());
    }
  }

  // draw ship and pos info
  mvwprintw(this->win, cy, cx, this->ship->getSymbol().c_str());
  mvwprintw(this->win, 1, 2, "%.1f / %.1f", sx, sy);
  mvwprintw(this->win, this->wheight - 3, 1, "y");
  mvwprintw(this->win, this->wheight - 2, 1, "└x");

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
