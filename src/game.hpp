#pragma once

#include <chrono>
#include <thread>

#include "ship/modules/capacitor.hpp"
#include "ship/modules/engine.hpp"
#include "ship/modules/generator.hpp"
#include "ship/modules/shieldgenerator.hpp"
#include "ship/os/shipos.hpp"
#include "ship/ship.hpp"
#include "tools/console.hpp"
#include "tools/log.hpp"

class Game {
 public:
  Game();
  void start();
  void render(ConsoleKey key);
  void renderWin(ConsoleKey key);

 private:
  Ship s;
  ShipOs os;

  double calcSimTime();
};
