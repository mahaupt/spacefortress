#pragma once

#include <chrono>
#include <future>
#include <random>
#include <thread>
#include <vector>

#include "objects/planet.hpp"
#include "objects/star.hpp"
#include "objects/station.hpp"
#include "ship/modules/capacitor.hpp"
#include "ship/modules/cargo.hpp"
#include "ship/modules/dockingport.hpp"
#include "ship/modules/engine.hpp"
#include "ship/modules/generator.hpp"
#include "ship/modules/lifesupport.hpp"
#include "ship/modules/sensor.hpp"
#include "ship/modules/shieldgenerator.hpp"
#include "ship/modules/shipai.hpp"
#include "ship/modules/weapon.hpp"
#include "ship/os/shipos.hpp"
#include "ship/ship.hpp"
#include "tools/console.hpp"
#include "tools/log.hpp"
#include "tools/vec2.hpp"

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
  void garbageCollector();
};
