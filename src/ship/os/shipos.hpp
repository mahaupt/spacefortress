#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "../../gameobject.hpp"
#include "../../tools/console.hpp"
#include "../../ui/window.hpp"
#include "../ship.hpp"
#include "helm.hpp"
#include "map.hpp"
#include "program.hpp"
#include "statusmonitor.hpp"
#include "terminal.hpp"

#define SHIPOS_VERSION "v0.2.1"
#define SHIPOS_VER "1"
#define SHIPOS_NAME "Rusty Leopard"

enum class ShipOsState { OFF, BOOTING, RUNNING, SHUTDOWN };

/**
 * Window and Process Manager for the Ship UI
 */
class ShipOs {
 public:
  ShipOs(Ship *ship, std::vector<GameObject *> *game_objects);
  ~ShipOs();
  void boot();
  void autostart();
  void render(ConsoleKey key);
  void renderWin(ConsoleKey key);
  double getUptime();
  ShipOsState getState() { return this->state; }
  void addProgram(shipos::Program *prog) { this->v_programs.push_back(prog); }

 private:
  Ship *ship;
  std::vector<GameObject *> *game_objects;
  ShipOsState state;

  std::chrono::time_point<std::chrono::steady_clock> boot_time;

  std::vector<shipos::Program *> v_programs;
  shipos::Program *main_terminal;
  bool windows_tabbed;

  void renderBoot(ConsoleKey key);
  void garbageCollector();
};
