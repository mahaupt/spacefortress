#include "game.hpp"

Game::Game() : s("Omega", 100) {
  this->s.addModule(new Generator("Generator MK I", 1, 1));
  this->s.addModule(new ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  this->s.addModule(new ShieldGenerator("Engine MK I", 1, 1, 1));
  this->s.addModule(new Capacitor("Capacitor MK I", 1, 100, 1, 10));
}

void Game::render(ConsoleKey key) {
  static auto last_start_time = std::chrono::steady_clock::now();
  auto start_time = std::chrono::steady_clock::now();
  double simTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                       start_time - last_start_time)
                       .count() /
                   1000.0;
  last_start_time = start_time;

  this->s.simulate(simTime);
  this->s.info();
  printw("Simulating %f seconds\n", simTime);
  printw("\nPress q to exit...\n");
}
