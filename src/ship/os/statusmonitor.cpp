#include "statusmonitor.hpp"

shipos::StatusMonitor::StatusMonitor(WINDOW* win, Ship* ship)
    : Program(win, ship) {}

void shipos::StatusMonitor::render(ConsoleKey key) {
  wprintw(this->win, "Ship Info %s\n", this->ship->getName().c_str());
  wprintw(this->win, "Hull: %f/%f\n", this->ship->getHull(),
          this->ship->getMaxHull());
  wprintw(this->win, "Shield: %f/%f\n", this->ship->getShield(),
          this->ship->getMaxShield());
  wprintw(this->win, "Energy: %f/%f\n", this->ship->getEnergyLevel(),
          this->ship->getEnergyTotalCapacity());
  wprintw(this->win, "%i Modules installed\n", this->ship->getModuleCount());
  wprintw(this->win, "\nPress q to exit...\n");
}
