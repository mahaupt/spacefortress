#pragma once

#include <chrono>
#include <thread>

#include "ship/modules/capacitor.hpp"
#include "ship/modules/engine.hpp"
#include "ship/modules/generator.hpp"
#include "ship/modules/shieldgenerator.hpp"
#include "ship/ship.hpp"
#include "tools/console.hpp"

class Game {
 public:
  Game();
  void render(ConsoleKey key);

 private:
  Ship s;
};
