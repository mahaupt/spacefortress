#include "sensor.hpp"

using namespace shipos;

Sensor::Sensor(Ship* ship) : Program(ship), selection(0), psensor(0) {}

Sensor::Sensor(Ship* ship, WindowAlignment alignment_x,
               WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y),
      selection(0),
      psensor(nullptr) {
  this->window->setTitle(Lang::get("program_sensor"));
}

void Sensor::render(ConsoleKey key) {
  if (this->psensor == nullptr)
    this->psensor = (module::Sensor*)this->ship->getFirstModule("Sensor");

  this->getWindowSize();

  // render list of objects
  if (this->psensor != nullptr) {
    // process keyboard input
    if (key == ConsoleKey::ARROW_UP && this->selection > 0) {
      this->selection--;
    }
    if (key == ConsoleKey::ARROW_DOWN) {
      this->selection++;
    }

    Vec2 spos = this->ship->getPos();

    // fetch and sort object list from sensor
    std::vector<GameObject*>* v = this->psensor->getScannedObjects();
    std::list<GameObject*> mlist(v->begin(), v->end());
    mlist.sort([spos](GameObject* a, GameObject* b) {
      Vec2 posa = a->getPos();
      Vec2 posb = b->getPos();
      posa -= spos;
      posb -= spos;
      return (posa.magnitude() < posb.magnitude());
    });

    // limit selection
    if (this->selection >= mlist.size()) {
      this->selection = mlist.size() - 1;
    }

    // draw object list
    int i = 0;
    mvwprintw(this->win, 1, 1, "#  Type      Name            Distance    RB");
    for (const auto& object : mlist) {
      Vec2 opos = object->getPos();
      opos -= spos;

      if (i == this->selection) {
        wattron(this->win, A_STANDOUT);
      }

      mvwprintw(this->win, i + 2, 1, "%i   ", i);
      wclrtoeol(this->win);
      mvwprintw(this->win, i + 2, 4, "%s         ", object->getType().c_str());
      mvwprintw(this->win, i + 2, 14, "%s               ",
                object->getName().c_str());
      mvwprintw(this->win, i + 2, 30, "%.3f AU       ", opos.magnitude());
      double angle = opos.angle() / 3.1416 * 180;
      if (angle < 0) angle += 360;
      mvwprintw(this->win, i + 2, 42, "%03.0f", angle);

      if (i == this->selection) {
        wattroff(this->win, A_STANDOUT);
      }
      i++;

      // limit drawing
      if (i + 2 >= this->wheight - 2) break;
    }

    mvwprintw(this->win, this->wheight - 2, 1,
              "c - call, l - lock, t - ap target");
  }

  Program::render(key);
}

void Sensor::getWindowSize() {
  getmaxyx(this->win, this->wheight, this->wwidth);
}