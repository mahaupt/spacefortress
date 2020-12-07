#pragma once

#include <chrono>
#include <future>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#include "objects/planet.hpp"
#include "objects/star.hpp"
#include "objects/station.hpp"
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
  void stop();

 private:
  bool running;
  std::weak_ptr<Ship> pship;
  std::shared_ptr<ShipOs> pshipos;

  std::vector<std::shared_ptr<GameObject>> game_objects;

  void createGameWorld();
  double calcSimTime();
  void garbageCollector();
};
