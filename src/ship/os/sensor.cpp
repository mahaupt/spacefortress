#include "sensor.hpp"

using namespace shipos;

Sensor::Sensor(Ship* ship)
    : Program(ship, "Sensor"), selection(0), psensor(0) {}

Sensor::Sensor(Ship* ship, WindowAlignment alignment_x,
               WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, "Sensor", alignment_x, alignment_y, size_x, size_y),
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
    std::vector<GameObject*>* v = this->psensor->getScannedObjects();
    if (v != nullptr) {
      // fetch and sort object list from sensor
      Vec2 spos = this->ship->getPos();
      std::list<GameObject*> mlist(v->begin(), v->end());
      mlist.sort([spos](GameObject* a, GameObject* b) {
        Vec2 posa = a->getPos();
        Vec2 posb = b->getPos();
        posa -= spos;
        posb -= spos;
        return (posa.magnitude() < posb.magnitude());
      });

      // process keyboard input
      if (key == ConsoleKey::ARROW_UP && this->selection > 0) {
        this->selection--;
      }
      if (key == ConsoleKey::ARROW_DOWN) {
        this->selection++;
      }
      // limit selection
      if (this->selection >= mlist.size()) {
        this->selection = mlist.size() - 1;
      }
      if ((char)key == 'l') {
        // lock target
        auto git = mlist.begin();
        std::advance(git, this->selection);
        if (*git != nullptr) {
          this->psensor->startLock(*git);
        }
      }
      if (key == ConsoleKey::BACKSPACE || key == ConsoleKey::BACKSPACE2) {
        this->psensor->clearLock();
      }

      // draw object list
      int i = 0;
      mvwprintw(this->win, 1, 1, "#  Type      Name            Distance    RB");
      GameObject* lock_go = this->psensor->getLockTarget();
      double lock_progress = this->psensor->getLockProgress();
      for (const auto& object : mlist) {
        if (object->getType() == "Projectile") continue;
        Vec2 opos = object->getPos();
        opos -= spos;

        if (i == this->selection) {
          wattron(this->win, A_STANDOUT);
        }

        // object it type name
        mvwprintw(this->win, i + 2, 1, "%2i   ", i);
        wclrtoeol(this->win);
        mvwprintw(this->win, i + 2, 4, "%s         ",
                  object->getType().c_str());
        mvwprintw(this->win, i + 2, 14, "%s               ",
                  object->getName().c_str());

        // object distance and relative bearing
        double magnitude = opos.magnitude();
        mvwprintw(this->win, i + 2, 30, "%6.3f AU       ", magnitude);
        double angle = opos.angle() / 3.1416 * 180;
        mvwprintw(this->win, i + 2, 42, "%03.0f", angle);

        // locking indicators
        if (lock_go == object) {
          // locking
          if (lock_progress == 1) {
            mvwprintw(this->win, i + 2, 46, "**locked**");
          } else {
            mvwprintw(this->win, i + 2, 46, "locking...");
          }
        }

        if (i == this->selection) {
          wattroff(this->win, A_STANDOUT);
        }
        i++;

        // limit drawing
        if (i + 2 >= this->wheight - 1) break;
      }

    } else {
      this->showError(4, Lang::get("program_map_sensoroffline"));
    }
  } else {
    this->showError(4, Lang::get("program_map_nosensor"));
  }

  Program::render(key);
}