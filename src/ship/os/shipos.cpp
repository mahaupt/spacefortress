#include "shipos.hpp"

ShipOs::ShipOs(Ship *ship) : ship(ship), state(ShipOsState::OFF) {}

ShipOs::~ShipOs() {
  for (size_t i = 0; i < this->v_programs.size(); i++) {
    delete v_programs[i];
  }
  v_programs.clear();

  for (size_t i = 0; i < this->v_windows.size(); i++) {
    delete v_windows[i];
  }
  v_windows.clear();
}

void ShipOs::boot() {
  this->state = ShipOsState::BOOTING;
  this->boot_time = std::chrono::steady_clock::now();

  Window *w1 = new Window(WindowAlignment::RIGHT, 0.3);
  w1->setTitle("Ship status: Omega");
  this->addWindow(w1);
  this->addProgram(new shipos::StatusMonitor(w1->getWin(), this->ship));

  Window *w2 = new Window(WindowAlignment::LEFT, 0.7);
  w2->setTitle("Ship status: Omega");
  this->addWindow(w2);
  this->addProgram(new shipos::StatusMonitor(w2->getWin(), this->ship));
}

void ShipOs::render(ConsoleKey key) {
  if (this->state == ShipOsState::BOOTING) {
    this->renderBoot();
  }
}

/**
 * Render all OS Programs and windows
 * @param key [description]
 */
void ShipOs::renderWin(ConsoleKey key) {
  if (this->state == ShipOsState::RUNNING) {
    for (size_t i = 0; i < this->v_programs.size(); i++) {
      v_programs[i]->render(key);
    }
    for (size_t i = 0; i < this->v_windows.size(); i++) {
      v_windows[i]->render(key);
    }
  }
}

/**
 * Gets uptime of shipos system in seconds
 * @return seconds of uptime
 */
double ShipOs::getUptime() {
  auto now = std::chrono::steady_clock::now();
  double uptime = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now - this->boot_time)
                      .count() /
                  1000.0;
  return uptime;
}

void ShipOs::renderBoot() {
  double uptime = this->getUptime();

  if (uptime < 4.0) {
    if (uptime > 0.0) printw("OMEGON (C) 2218 Systems Inc.\n");
    if (uptime > 0.1) printw("BIOS Date 20-11-23 Ver.: 1.5.18\n");
    if (uptime > 0.2) printw("CPU: Xyntix R9 CPU @ 81 GHz\n");
    if (uptime > 0.2) printw("\n");

    if (uptime > 0.3) printw("Memory Test: ");
    if (uptime > 1.3) printw("8 TB OK\n");
    if (uptime > 1.4) printw("Initializing Hardware: ");
    if (uptime > 1.9) printw("182 Modules OK\n");
    if (uptime > 2.0) printw("\n");

    if (uptime > 2.1) printw("Loading Bootloader");
    if (uptime > 2.6) printw(".");
    if (uptime > 3.1) printw(".");
    if (uptime > 3.6) printw(".");
  }
  if (uptime > 4.0 && uptime < 9.9) {
    if (uptime > 4.0) printw("ShipOs " SHIPOS_VERSION "\n");
    if (uptime > 4.1)
      printw("Welcome to ShipOs " SHIPOS_VER " (" SHIPOS_NAME ")!\n");
    if (uptime > 4.2) printw("\n");

    if (uptime > 4.5) printw("Entering non-interactive startup\n");
    if (uptime > 4.5) printw("Applying CPU microcode updates\n");
    if (uptime > 4.6) printw("Checking for hardware changes\n");
    if (uptime > 4.7) printw("Bridging up eth0 interface\n");
    if (uptime > 4.7) printw("Determing IP information for eth0");
    if (uptime > 5.0) printw(".");
    if (uptime > 5.3) printw(".\n\n");

    if (uptime > 5.4) printw("Starting audit\n");
    if (uptime > 5.5) printw("Starting restorecond\n");
    if (uptime > 5.6) printw("Starting system logger\n");
    if (uptime > 5.7) printw("Starting kernel logger\n");
    if (uptime > 5.8) printw("Starting portmap\n");
    if (uptime > 5.9) printw("Starting quantumd\n");
    if (uptime > 6.0) printw("Starting subsystems");
    if (uptime > 7.0) printw(".");
    if (uptime > 8.0) printw(".");
    if (uptime > 9.0) printw(".");
  }

  // finish boot sequence
  if (uptime > 10.0) this->state = ShipOsState::RUNNING;
}
