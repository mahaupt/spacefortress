#include "console.hpp"
#include "game.hpp"
#include "logger.hpp"
#include "menu.hpp"

enum MainState { MAIN_MENU, SETTINGS, CONNECT, GAME };

bool p_running = true;
MainState main_state = MAIN_MENU;

/**
 * Ends program (callback)
 */
void endProgram(void) { p_running = false; }
void startGame(void) { main_state = GAME; }

/**
 * This is the main state machine for the program
 * @return 0
 */
int main() {
  Logger log(ALL);
  log.log("start", DEBUG);
  Console console;

  Menu main_menu;
  main_menu.addMenuEntry("Create Crew", &startGame);
  main_menu.addMenuEntry("Join Crew", &startGame);
  main_menu.addMenuEntry("Exit", &endProgram);

  Game game;

  ConsoleKey key = NONE;
  while (p_running) {
    clear();

    switch (main_state) {
      case MAIN_MENU:
        main_menu.render(key);
        break;
      case GAME:
        game.render();
        break;
    }

    refresh();

    timeout(100);
    key = console.getKey();

    if (key == KEY_Q) {
      break;
    }
  }

  return 0;
}
