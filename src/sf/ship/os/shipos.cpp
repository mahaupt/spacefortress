#include "shipos.hpp"

ShipOs::ShipOs(Ship *ship) : ship(ship), state(ShipOsState::OFF) {
  this->main_terminal = 0;
}

/**
 * removing all remaining heap classes from memory
 */
ShipOs::~ShipOs() {
  for (const auto &program : this->v_programs) {
    delete program;
  }
  v_programs.clear();

  // main terminal
  if (this->main_terminal != 0) {
    delete this->main_terminal;
    this->main_terminal = 0;
  }
}

void ShipOs::boot() {
  this->state = ShipOsState::BOOTING;
  this->boot_time = std::chrono::steady_clock::now();
}

/**
 * Autostarts default programs
 */
void ShipOs::autostart() {
  Console::sclear();

  // background terminal
  this->main_terminal = new shipos::Terminal(this->ship, &(this->v_programs));
  this->main_terminal->setState(shipos::ProgramState::HALT);

  // nav overview programs
  this->addProgram(new shipos::Map(this->ship, WindowAlignment::LEFT,
                                   WindowAlignment::TOP, 0.7, 1.0));
  this->addProgram(new shipos::StatusMonitor(this->ship, WindowAlignment::RIGHT,
                                             WindowAlignment::TOP, 0.3, 0.5));
  this->addProgram(new shipos::Helm(this->ship, WindowAlignment::RIGHT,
                                    WindowAlignment::BOTTOM, 0.3, 0.5));
}

/**
 * Render the main window - (Terminal)
 * @param key Console Key
 */
void ShipOs::render(ConsoleKey key) {
  // check ship status
  if (this->ship == nullptr || !this->ship->isAlive()) {
    this->ship = nullptr;
    Console::sclear();
    printw("your ship has been destroyed");
    return;
  }

  if (this->state == ShipOsState::BOOTING) {
    this->renderBoot(key);
  }
  if (this->state == ShipOsState::RUNNING) {
    if (this->main_terminal != 0 &&
        this->main_terminal->getState() == shipos::ProgramState::RUN) {
      this->main_terminal->render(key);
    }
  }
}

/**
 * Render all OS Programs and windows
 * @param key [description]
 */
void ShipOs::renderWin(ConsoleKey key) {
  if (this->ship == nullptr) return;

  // render programs
  if (this->state == ShipOsState::RUNNING) {
    for (const auto &program : this->v_programs) {
      if (program->getState() == shipos::ProgramState::RUN) {
        program->render(key);
      }
    }

    // tab control - hide and show programs
    if (key == ConsoleKey::TAB) {
      auto pstate = shipos::ProgramState::HALT;
      auto wstate = WindowState::HIDDEN;
      if (this->main_terminal->getState() != pstate &&
          this->v_programs.size() > 0) {
        // restore windows, block background terminal
        // only do this when there are actually open windows to display
        pstate = shipos::ProgramState::RUN;
        wstate = WindowState::VISIBLE;
        this->main_terminal->setState(shipos::ProgramState::HALT);
      } else {
        // hide windows, run terminal
        this->main_terminal->setState(shipos::ProgramState::RUN);
        Console::sclear();
      }
      for (size_t i = 0; i < this->v_programs.size(); i++) {
        this->v_programs[i]->setState(pstate);
        this->v_programs[i]->setWinState(wstate);
      }
    }
  }

  if (key != ConsoleKey::NONE) Log::info("Key: " + std::to_string((int)key));

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

void ShipOs::renderBoot(ConsoleKey key) {
  double uptime = this->getUptime();
  static size_t drawline = 0;
  static double lastuptime = uptime;
  
  // reset statics
  if (uptime - lastuptime < 0) {
    lastuptime = uptime;
    drawline = 0;
  }
  
  if (uptime - lastuptime >= 0.1 || key == ConsoleKey::SPACE) {
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
  if (drawline == 100 || key == ConsoleKey::SPACE) {
    this->state = ShipOsState::RUNNING;
    this->autostart();
  }
}

/**
 * Collects terminated programs and removes them from Memory
 * Also closes empty windows
 */
void ShipOs::garbageCollector() {
  auto it = this->v_programs.begin();
  while (it != this->v_programs.end()) {
    if ((*it)->getState() == shipos::ProgramState::TERM) {
      delete *it;
      it = this->v_programs.erase(it);

      // Console::sclear();
    } else {
      it++;
    }
  }
}
