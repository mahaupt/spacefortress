#include "statusmonitor.hpp"

shipos::StatusMonitor::StatusMonitor(Ship* ship) : Program(ship) {}
shipos::StatusMonitor::StatusMonitor(Ship* ship, WindowAlignment alignment_x,
                                     WindowAlignment alignment_y, double size_x,
                                     double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y) {
  this->window->setTitle(Lang::get("program_smon"));
}

void shipos::StatusMonitor::render(ConsoleKey key) {
  std::string regstr = Lang::get("program_smon_reg") + ": %s";
  mvwprintw(this->win, 1, 1, regstr.c_str(), this->ship->getName().c_str());

  double hull_ratio = this->ship->getHull() / this->ship->getMaxHull();
  if (hull_ratio < 0.1) {
    wattron(this->win, A_BLINK);
  }
  if (hull_ratio < 0.3) {
    wattron(this->win, A_BOLD);
  }
  std::string hulstr = Lang::get("program_smon_hul") + ": %.1f/%.1f";
  mvwprintw(this->win, 2, 1, hulstr.c_str(), this->ship->getHull(),
            this->ship->getMaxHull());
  if (hull_ratio < 0.1) {
    wattroff(this->win, A_BLINK);
  }
  if (hull_ratio < 0.3) {
    wattroff(this->win, A_BOLD);
  }

  double shield_ratio = this->ship->getShield() / this->ship->getMaxShield();
  if (shield_ratio < 0.1) {
    wattron(this->win, A_BLINK);
  }
  if (shield_ratio < 0.3) {
    wattron(this->win, A_BOLD);
  }
  std::string sldstr = Lang::get("program_smon_sld") + ": %.1f/%.1f";
  mvwprintw(this->win, 3, 1, sldstr.c_str(), this->ship->getShield(),
            this->ship->getMaxShield());
  if (shield_ratio < 0.1) {
    wattroff(this->win, A_BLINK);
  }
  if (shield_ratio < 0.3) {
    wattroff(this->win, A_BOLD);
  }

  double energy_ratio =
      this->ship->getEnergyLevel() / this->ship->getEnergyTotalCapacity();
  if (energy_ratio < 0.1) {
    wattron(this->win, A_BLINK);
  }
  if (energy_ratio < 0.3) {
    wattron(this->win, A_BOLD);
  }
  std::string enrstr = Lang::get("program_smon_enr") + ": %.1f/%.1f";
  mvwprintw(this->win, 4, 1, enrstr.c_str(), this->ship->getEnergyLevel(),
            this->ship->getEnergyTotalCapacity());
  if (energy_ratio < 0.1) {
    wattroff(this->win, A_BLINK);
  }
  if (energy_ratio < 0.3) {
    wattroff(this->win, A_BOLD);
  }

  std::string modstr = Lang::get("program_smon_mod") + ": %i" +
                       Lang::get("program_smon_installed");
  mvwprintw(this->win, 5, 1, modstr.c_str(), this->ship->getModuleCount());

  // render window
  Program::render(key);
}
