#include "statusmonitor.hpp"

shipos::StatusMonitor::StatusMonitor(WINDOW* win, Ship* ship)
    : Program(win, ship) {}

void shipos::StatusMonitor::render(ConsoleKey key) {
  mvwprintw(this->win, 1, 1, "H: %.1f/%.1f", this->ship->getHull(),
            this->ship->getMaxHull());
  mvwprintw(this->win, 2, 1, "S: %.1f/%.1f", this->ship->getShield(),
            this->ship->getMaxShield());
  mvwprintw(this->win, 3, 1, "E: %.1f/%.1f", this->ship->getEnergyLevel(),
            this->ship->getEnergyTotalCapacity());
  mvwprintw(this->win, 4, 1, "%i Modules installed",
            this->ship->getModuleCount());
}
