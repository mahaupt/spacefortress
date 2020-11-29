#include "offensive.hpp"

using namespace shipos;

Offensive::Offensive(Ship* ship)
    : Program(ship, "Offensive"), selection(0), psensor(nullptr) {}

Offensive::Offensive(Ship* ship, WindowAlignment alignment_x,
                     WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, "Offensive", alignment_x, alignment_y, size_x, size_y),
      selection(0),
      psensor(nullptr) {
  this->window->setTitle(Lang::get("program_offensive"));
}

void Offensive::render(ConsoleKey key) {
  this->getWindowSize();

  if (this->psensor == nullptr)
    this->psensor = (module::Sensor*)this->ship->getFirstModule("Sensor");

  // target information
  if (this->psensor != nullptr) {
    GameObject* lock_obj = this->psensor->getLockTarget();
    double lock_prog = this->psensor->getLockProgress();
    mvwprintw(this->win, 1, 1, Lang::get("program_offensive_tgt").c_str());
    if (lock_obj != nullptr) {
      // name, locking %
      mvwprintw(this->win, 2, 1, "%s", lock_obj->getName().c_str());
      wclrtoeol(this->win);
      mvwprintw(this->win, 2, 16, "%.0f%%", lock_prog * 100);

      // distance and bearing
      Vec2 vec = lock_obj->getPos() - this->ship->getPos();
      double ang = vec.angle() / 3.146 * 180;
      mvwprintw(this->win, 2, 23, "%6.3f AU", vec.magnitude());
      mvwprintw(this->win, 2, 35, "%03.0f°", ang);

      // vel, rel. vel,
      Vec2 vel = lock_obj->getVel();
      Vec2 relvel = vel - this->ship->getVel();
      mvwprintw(this->win, 3, 3, "abs: %4.1f mAU/s", vel.magnitude() * 1000.0);
      wclrtoeol(this->win);
      mvwprintw(this->win, 3, 25, "rel: %4.1f mAU/s",
                relvel.magnitude() * 1000.0);
    } else {
      mvwprintw(this->win, 2, 1, Lang::get("program_offensive_none").c_str());
      wclrtoeol(this->win);
      wmove(this->win, 3, 1);
      wclrtoeol(this->win);
    }
  } else {
    this->showError(1, Lang::get("program_map_nosensor"));
  }

  // weapon page keyboard
  if (key == ConsoleKey::ARROW_UP && this->selection > 0) {
    this->selection--;
  }
  if (key == ConsoleKey::ARROW_DOWN) {
    this->selection++;
  }

  // weapon page
  mvwprintw(this->win, 5, 1, Lang::get("program_offensive_weapons").c_str());
  int i = 0;
  for (const auto& module : *(this->ship->getModules())) {
    if (module->getType() == "Weapon") {
      if (this->selection == i) {
        // standout
        wattron(this->win, A_STANDOUT);

        // process keyboard commands
        if ((char)key == 'n') {
          bool a = ((module::Weapon*)module)->getActive();
          ((module::Weapon*)module)->setActive(!a);
        }
        if ((char)key == 'm') {
          bool a = ((module::Weapon*)module)->getAutofire();
          ((module::Weapon*)module)->setAutofire(!a);
        }
      }

      mvwprintw(this->win, i + 6, 1, "%s          ", module->getName().c_str());

      // module is online
      if (module->isOnline()) {
        mvwprintw(this->win, i + 6, 20, "l:%i  a:%i  c:%3.0f%%",
                  ((module::Weapon*)module)->getActive(),
                  ((module::Weapon*)module)->getAutofire(),
                  ((module::Weapon*)module)->getCharge() * 100);
      } else {
        mvwprintw(this->win, i + 6, 20, "**offline**");
      }

      if (this->selection == i) {
        wattroff(this->win, A_STANDOUT);
      }

      i++;
    }
  }
  // limit selection
  if (this->selection >= i && i > 0) {
    this->selection = i - 1;
  }

  if (i == 0) {
    this->showCentered(6, Lang::get("program_offensive_weapons_error"), A_BOLD);
  }

  Program::render(key);
}