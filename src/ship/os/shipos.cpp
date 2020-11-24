#include "shipos.hpp"

ShipOs::ShipOs(Ship *ship) : ship(ship), state(ShipOsState::OFF) {}

/**
 * removing all remaining dynamic classes from memory
 */
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
}

/**
 * Autostarts default programs
 */
void ShipOs::autostart() {
  Window *w1 = new Window(WindowAlignment::RIGHT, 0.3);
  w1->setTitle("Status Monitor");
  this->addWindow(w1);
  this->addProgram(new shipos::StatusMonitor(w1->getWin(), this->ship));

  Window *w2 = new Window(WindowAlignment::LEFT, 0.7);
  w2->setTitle("ShipOS Terminal");
  this->addWindow(w2);
  this->addProgram(new shipos::Terminal(w2->getWin(), this->ship));
}

/**
 * Render the main window - (Terminal)
 * @param key Console Key
 */
void ShipOs::render(ConsoleKey key) {
  if (this->state == ShipOsState::BOOTING) {
    this->renderBoot();
  }
  if (this->state == ShipOsState::RUNNING) {
    mvprintw(0, 0, "ShipOS running...");
    mvprintw(1, 0, "Processes: %i", v_programs.size());
    mvprintw(2, 0, "Windows: %i", v_windows.size());
  }
}

/**
 * Render all OS Programs and windows
 * @param key [description]
 */
void ShipOs::renderWin(ConsoleKey key) {
  // render programs
  if (this->state == ShipOsState::RUNNING) {
    for (size_t i = 0; i < this->v_programs.size(); i++) {
      if (v_programs[i]->getState() == shipos::ProgramState::RUN) {
        v_programs[i]->render(key);
      }

      if ((char)key == '3' || (char)key == '1') {
        v_programs[i]->setState(shipos::ProgramState::RUN);
      }
      if ((char)key == '4' || (char)key == '2') {
        v_programs[i]->setState(shipos::ProgramState::HALT);
      }
      if ((char)key == '5') {
        v_programs[i]->setState(shipos::ProgramState::TERM);
      }
    }

    // render windows
    for (size_t i = 0; i < this->v_windows.size(); i++) {
      if (v_windows[i]->getState() == WindowState::VISIBLE) {
        v_windows[i]->render(key);
      }

      if ((char)key == '1') {
        v_windows[i]->setState(WindowState::VISIBLE);
      }
      if ((char)key == '2') {
        v_windows[i]->setState(WindowState::HIDDEN);
      }
    }

    if ((char)key == '6') {
      this->autostart();
    }
  }

  // at the end
  this->garbageCollector();
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
  static size_t drawline = 0;
  static double lastuptime = uptime;
  if (uptime - lastuptime >= 0.1) {
    drawline++;
    lastuptime = uptime;
  } else {
    return;
  }

  if (drawline == 1) Console::sclear();
  if (drawline == 1) mvprintw(0, 0, "OMEGON (C) 2218 Systems Inc.");
  if (drawline == 2) mvprintw(1, 0, "BIOS Date 20-11-23 Ver.: 1.5.18");
  if (drawline == 3) mvprintw(2, 0, "CPU: Xyntix R9 CPU @ 81 GHz");

  if (drawline == 4) mvprintw(4, 0, "Memory Test: ");
  if (drawline == 13) mvprintw(4, 13, "8 TB OK");
  if (drawline == 14) mvprintw(5, 0, "Initializing Hardware: ");
  if (drawline == 19) mvprintw(5, 23, "182 Modules OK");

  if (drawline == 21) mvprintw(7, 0, "Loading Bootloader");
  if (drawline == 26) printw(".");
  if (drawline == 31) printw(".");
  if (drawline == 36) printw(".");

  if (drawline == 40) Console::sclear();

  if (drawline == 40) mvprintw(0, 0, "ShipOs " SHIPOS_VERSION "");
  if (drawline == 41)
    mvprintw(1, 0, "Welcome to ShipOs " SHIPOS_VER " (" SHIPOS_NAME ")!");

  if (drawline == 45) mvprintw(3, 0, "Entering non-interactive startup");
  if (drawline == 45) mvprintw(4, 0, "Applying CPU microcode updates");
  if (drawline == 46) mvprintw(5, 0, "Checking for hardware changes");
  if (drawline == 47) mvprintw(6, 0, "Bridging up eth0 interface");
  if (drawline == 47) mvprintw(7, 0, "Determing IP information for eth0");
  if (drawline == 50) printw(".");
  if (drawline == 53) printw(".");

  if (drawline == 54) mvprintw(9, 0, "Starting audit");
  if (drawline == 55) mvprintw(10, 0, "Starting restorecond");
  if (drawline == 56) mvprintw(11, 0, "Starting system logger");
  if (drawline == 57) mvprintw(12, 0, "Starting kernel logger");
  if (drawline == 58) mvprintw(13, 0, "Starting portmap");
  if (drawline == 59) mvprintw(14, 0, "Starting quantumd");
  if (drawline == 60) mvprintw(15, 0, "Starting subsystems");
  if (drawline == 70) printw(".");
  if (drawline == 80) printw(".");
  if (drawline == 90) printw(".");

  // finish boot sequence
  if (drawline == 100) {
    this->state = ShipOsState::RUNNING;
    this->autostart();
  }
}

/**
 * Collects terminated programs and removes them from Memory
 * Also closes empty windows
 */
void ShipOs::garbageCollector() {
  for (size_t i = 0; i < this->v_programs.size(); i++) {
    // terminated program
    if (v_programs[i]->getState() == shipos::ProgramState::TERM) {
      WINDOW *win = v_programs[i]->getWin();

      // try to close window
      if ((size_t)win > 0 && win != stdscr) {
        delete v_programs[i];
        v_programs.erase(v_programs.begin() + i);
        this->closeWindow(win);
        Console::sclear();
        return;  // return to avoid screwing with the iteration
      }
    }
  }
}

/**
 * searches through window vector and deletes windows
 * @param win WINDOW pointer
 */
void ShipOs::closeWindow(WINDOW *win) {
  for (size_t i = 0; i < this->v_windows.size(); i++) {
    if (this->v_windows[i]->getWin() == win) {
      delete this->v_windows[i];
      v_windows.erase(v_windows.begin() + i);
      return;
    }
  }
}
