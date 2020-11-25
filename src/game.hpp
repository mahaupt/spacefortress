#pragma once

#include <chrono>
#include <future>
#include <thread>
#include <vector>

#include "objects/planet.hpp"
#include "objects/star.hpp"
#include "objects/station.hpp"
#include "ship/modules/capacitor.hpp"
#include "ship/modules/cargo.hpp"
#include "ship/modules/engine.hpp"
#include "ship/modules/generator.hpp"
#include "ship/modules/lifesupport.hpp"
#include "ship/modules/shieldgenerator.hpp"
#include "ship/os/shipos.hpp"
#include "ship/ship.hpp"
#include "tools/console.hpp"
#include "tools/log.hpp"

class Game {
 public:
  Game();
  ~Game();
  void start();
  void render(ConsoleKey key);
  void renderWin(ConsoleKey key);

 private:
  Ship s;
  ShipOs os;

  std::vector<GameObject *> game_objects;

  double calcSimTime();
};
