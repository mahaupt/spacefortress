#include "game.hpp"

Game::Game() : s("Omega", 100) {
  this->s.addModule(new Generator("Generator MK I", 1, 1));
  this->s.addModule(new ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  this->s.addModule(new ShieldGenerator("Engine MK I", 1, 1, 1));
  this->s.addModule(new Capacitor("Capacitor MK I", 1, 100, 1, 10));
}

void Game::render() {
  static double simTime = 0.1;

  auto start_time = std::chrono::steady_clock::now();

  this->s.simulate(simTime);
  this->s.info();
  printw("Simulating %f seconds\n", simTime);
  printw("\nPress q to exit...\n");
  refresh();

  // non blocking getch
  timeout(100);
  int cmd;
  if ((cmd = getch()) == 'q') {
    // break;
  }

  auto end_time = std::chrono::steady_clock::now();
  simTime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                  start_time)
                .count() /
            1000.0;
}
