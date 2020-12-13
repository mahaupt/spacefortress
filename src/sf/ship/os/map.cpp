#include "map.hpp"

shipos::Map::Map(Ship* ship) : Program(ship, "Map"), zoom(5), ptr_sensor(0) {}

shipos::Map::Map(Ship* ship, WindowAlignment alignment_x,
                 WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, "Map", alignment_x, alignment_y, size_x, size_y),
      zoom(5),
      ptr_sensor(nullptr) {
  this->window->setTitle(Lang::get("program_map"));
}

void shipos::Map::render(ConsoleKey key) {
  // find ship modules
  if (this->ptr_sensor == nullptr)
    this->ptr_sensor = (module::Sensor*)this->ship->getFirstModule("Sensor");

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
  int cx = (int)round(this->wwidth / 2.0);
  int cy = (int)round(this->wheight / 2.0);
  Vec2 spos = this->ship->getPos();

  // draw objects with sensor
  if (this->ptr_sensor != nullptr) {
    auto gobjects = this->ptr_sensor->getScannedObjects();
    if (gobjects != nullptr) {
      // get sensor lock target
      auto plocktgt = this->ptr_sensor->getLockTarget().lock();

      for (const auto& gobject : *gobjects) {
        // get position of object
        Vec2 gpos = gobject->getPos();
        gpos -= spos;  // vec from ship to obj
        gpos *= this->zoom;

        // calc screen position
        int spx = (int)round(cx + gpos.getX());
        int spy = (int)round(cy - gpos.getY());

        // object is in map screen
        if (spx > 1 && spx < this->wwidth - 2 && spy > 1 &&
            spy < this->wheight - 2) {
          if (plocktgt == gobject) {
            wattron(this->win, COLOR_PAIR((int)ConsoleColor::MAGENTA));
          }

          mvwprintw(this->win, spy, spx, gobject->getSymbol().c_str());

          if (plocktgt == gobject) {
            wattroff(this->win, COLOR_PAIR((int)ConsoleColor::MAGENTA));
          }
        }
      }
    } else {
      // display sensor offline
      this->showError(this->wheight - 5,
                      Lang::get("program_map_sensoroffline"));
    }
  } else {
    // display no sensor blinking
    this->showError(this->wheight - 5, Lang::get("program_map_nosensor"));
  }

  // draw ship and pos info
  wattron(this->win, COLOR_PAIR((int)ConsoleColor::GREEN));
  mvwprintw(this->win, cy, cx, this->ship->getSymbol().c_str());
  wattroff(this->win, COLOR_PAIR((int)ConsoleColor::GREEN));
  mvwprintw(this->win, 1, 2, "%.3f / %.3f    %.1f mAU/s", spos.getX(),
            spos.getY(), (this->ship->getVel().magnitude() * 1000.0f));
  mvwprintw(this->win, this->wheight - 3, 1, "y");
  mvwprintw(this->win, this->wheight - 2, 1, "└x");
  mvwprintw(this->win, this->wheight - 2, this->wwidth - 4, "x%i", this->zoom);

  // render window
  Program::render(key);
}
