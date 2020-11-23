#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "../../tools/console.hpp"

enum class ShipOsState { OFF, BOOTING, RUNNING, SHUTDOWN };

/**
 * Window and Process Manager for the Ship UI
 */
class ShipOs {
 public:
  ShipOs();
  void boot();
  void render(ConsoleKey key);
  void renderWin(ConsoleKey key);
  double getUptime();
  ShipOsState getState() { return this->state; }

 private:
  ShipOsState state;
  std::chrono::time_point<std::chrono::steady_clock> boot_time;

  void renderBoot();
};
