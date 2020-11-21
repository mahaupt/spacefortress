#pragma once

#include <chrono>
#include <thread>

#include "ship/modules/capacitor.hpp"
#include "ship/modules/engine.hpp"
#include "ship/modules/generator.hpp"
#include "ship/modules/shieldgenerator.hpp"
#include "ship/ship.hpp"

class Game {
 public:
  Game();
  void render();

 private:
  Ship s;
};
