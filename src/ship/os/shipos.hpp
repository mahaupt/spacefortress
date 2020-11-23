#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "../../tools/console.hpp"
#include "../../ui/window.hpp"
#include "../ship.hpp"
#include "program.hpp"
#include "statusmonitor.hpp"

#define SHIPOS_VERSION "v0.1.4"
#define SHIPOS_VER "1"
#define SHIPOS_NAME "Rusty Leopard"

enum class ShipOsState { OFF, BOOTING, RUNNING, SHUTDOWN };

/**
 * Window and Process Manager for the Ship UI
 */
class ShipOs {
 public:
  ShipOs(Ship *ship);
  ~ShipOs();
  void boot();
  void render(ConsoleKey key);
  void renderWin(ConsoleKey key);
  double getUptime();
  ShipOsState getState() { return this->state; }
  void addWindow(Window *win) { this->v_windows.push_back(win); }
  void addProgram(shipos::Program *prog) { this->v_programs.push_back(prog); }

 private:
  Ship *ship;
  ShipOsState state;

  std::chrono::time_point<std::chrono::steady_clock> boot_time;

  std::vector<Window *> v_windows;
  std::vector<shipos::Program *> v_programs;

  void renderBoot();
  void garbageCollector();
  void closeWindow(WINDOW *win);
};
