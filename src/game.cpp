#include "game.hpp"

Game::Game() : s("Omega", 100) {
  this->s.addModule(new Generator("Generator MK I", 1, 1));
  this->s.addModule(new ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  this->s.addModule(new ShieldGenerator("Engine MK I", 1, 1, 1));
  this->s.addModule(new Capacitor("Capacitor MK I", 1, 100, 1, 10));

  Log::info("game module loaded");
}

void Game::start() {
  this->os.boot();
  Log::info("game start");
}

void Game::render(ConsoleKey key) {
  double sim_time = this->calcSimTime();
  this->s.simulate(sim_time);

  this->os.render(key);

  if (this->os.getState() == ShipOsState::RUNNING) {
    this->s.info();
    printw("Simulating %f seconds\n", sim_time);
    printw("\nPress q to exit...\n");
  }
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
