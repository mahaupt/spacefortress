#include "map.hpp"

shipos::Map::Map(Ship* ship) : Program(ship), zoom(5), ptr_sensor(0) {}

shipos::Map::Map(Ship* ship, WindowAlignment alignment_x,
                 WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y),
      zoom(5),
      ptr_sensor(0) {
  this->window->setTitle(Lang::get("program_map"));
}

void shipos::Map::render(ConsoleKey key) {
  this->getWindowSize();

  werase(this->win);

  // zoom levels
  if ((char)key == '-' && zoom > 1) {
    zoom--;
  }
  if ((char)key == '+' && zoom < 20) {
    zoom++;
  }

  // get ship pos and center pos
  int cx = round(this->wwidth / 2.0);
  int cy = round(this->wheight / 2.0);
  Vec2 spos = this->ship->getPos();

  // make sure we have a sensor object
  this->findShipSensor();

  // draw objects with sensor
  if (this->ptr_sensor != 0) {
    auto gobjects = this->ptr_sensor->getScannedObjects();
    if (gobjects != 0) {
      for (const auto& gobject : *gobjects) {
        // get position of object
        Vec2 gpos = gobject->getPos();
        gpos -= spos;  // vec from ship to obj
        gpos *= this->zoom;

        // calc screen position
        int spx = round(cx + gpos.getX());
        int spy = round(cy - gpos.getY());

        // object is in map screen
        if (spx > 1 && spx < this->wwidth - 2 && spy > 1 &&
            spy < this->wheight - 2) {
          mvwprintw(this->win, spy, spx, gobject->getSymbol().c_str());
        }
      }
    } else {
      // display sensor offline
      wattron(this->win, A_BLINK | A_BOLD);
      std::string error = Lang::get("program_map_sensoroffline");
      int err_x = round((this->wwidth - error.length()) / 2.0);
      mvwprintw(this->win, this->wheight - 5, err_x, error.c_str());
      wattroff(this->win, A_BLINK | A_BOLD);
    }
  } else {
    // display no sensor blinking
    wattron(this->win, A_BLINK | A_BOLD);
    std::string error = Lang::get("program_map_nosensor");
    int err_x = round((this->wwidth - error.length()) / 2.0);
    mvwprintw(this->win, this->wheight - 5, err_x, error.c_str());
    wattroff(this->win, A_BLINK | A_BOLD);
  }

  // draw ship and pos info
  mvwprintw(this->win, cy, cx, this->ship->getSymbol().c_str());
  mvwprintw(this->win, 1, 2, "%.3f / %.3f    %.1f mAU/s", spos.getX(),
            spos.getY(), (this->ship->getVel().magnitude() * 1000.0f));
  mvwprintw(this->win, this->wheight - 3, 1, "y");
  mvwprintw(this->win, this->wheight - 2, 1, "└x");
  mvwprintw(this->win, this->wheight - 2, this->wwidth - 4, "x%i", this->zoom);

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

/**
 * Find ship sensor to display map with
 */
void shipos::Map::findShipSensor() {
  if (this->ptr_sensor != 0) return;

  // search through ship modules
  for (const auto& module : *(ship->getModules())) {
    if (module->getType() == "Sensor") {
      this->ptr_sensor = (Sensor*)module;
      return;
    }
  }
}
