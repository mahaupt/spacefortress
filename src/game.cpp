#include "game.hpp"

Game::Game() : s("Omega", 100), os(&s, &game_objects) {
  // add player ship
  this->s.setPos(-1, 0.1);
  this->s.addModule(new Generator("Generator MK I", 1, 1));
  this->s.addModule(new ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  this->s.addModule(new ShieldGenerator("Engine MK I", 1, 1, 1));
  this->s.addModule(new Capacitor("Capacitor MK I", 1, 100, 1, 10));

  // add planets
  this->game_objects.push_back(new go::Planet("Rix", 1, 1));
  this->game_objects.push_back(new go::Planet("Lira", 2, -1));
  this->game_objects.push_back(new go::Planet("Omecron", -3, 0));
  this->game_objects.push_back(new go::Planet("Deca", -4, -2));
  this->game_objects.push_back(new go::Planet("Zyppr", 5, 2));

  // add star
  this->game_objects.push_back(new go::Star("Mycra", 0, 0));

  // add Station
  this->game_objects.push_back(new go::Station("Mycra Outpost", -1, 0));

  Log::info("game module loaded");
}

/**
 * free all game objects
 */
Game::~Game() {
  for (size_t i = 0; i < this->game_objects.size(); i++) {
    delete this->game_objects[i];
    this->game_objects[i] = 0;
  }
  this->game_objects.clear();
}

void Game::start() {
  this->os.boot();
  Log::info("game start");
}

void Game::render(ConsoleKey key) {
  double sim_time = this->calcSimTime();
  this->s.simulate(sim_time);

  this->os.render(key);
}

void Game::renderWin(ConsoleKey key) { this->os.renderWin(key); }

double Game::calcSimTime() {
  static auto last_start_time = std::chrono::steady_clock::now();
  auto start_time = std::chrono::steady_clock::now();
  double sim_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                        start_time - last_start_time)
                        .count() /
                    1000.0;
  last_start_time = start_time;

  return sim_time;
}
