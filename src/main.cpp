#include <chrono>
#include <thread>

#include "console.hpp"
#include "logger.hpp"
#include "ship/modules/capacitor.hpp"
#include "ship/modules/engine.hpp"
#include "ship/modules/generator.hpp"
#include "ship/modules/shieldgenerator.hpp"
#include "ship/ship.hpp"

int main() {
  Logger log(ALL);
  log.log("start", DEBUG);
  Console console;

  Ship s = Ship("Omega", 100);
  s.addModule(new Generator("Generator MK I", 1, 1));
  s.addModule(new ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  s.addModule(new ShieldGenerator("Engine MK I", 1, 1, 1));
  s.addModule(new Capacitor("Capacitor MK I", 1, 100, 1, 10));

  int cmd;
  double simTime = 0.1;

  noecho();

  curs_set(0);

  while (true) {
    clear();
    auto start_time = std::chrono::steady_clock::now();

    s.simulate(simTime);
    s.info();
    printw("Simulating %f seconds\n", simTime);
    printw("\nPress q to exit...\n");

    // non blocking getch
    timeout(100);
    if ((cmd = getch()) == 'q') {
      break;
    }

    auto end_time = std::chrono::steady_clock::now();
    simTime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                    start_time)
                  .count() /
              1000.0;
  }

  return 0;
}
