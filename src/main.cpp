#include "game.hpp"
#include "menu.hpp"
#include "tools/console.hpp"
#include "tools/logger.hpp"

enum MainState { MAIN_MENU, SETTINGS, CONNECT, GAME };

bool p_running = true;
MainState main_state = MAIN_MENU;

/**
 * Callbacks
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
  main_menu.addMenuBannerLine("   ____                 ____         __");
  main_menu.addMenuBannerLine(
      "  / _____ ___ ________ / _____  ____/ /________ ___ ___");
  main_menu.addMenuBannerLine(
      " _\\ \\/ _ / _ `/ __/ -_/ _// _ \\/ __/ __/ __/ -_(_-<(_-<");
  main_menu.addMenuBannerLine(
      "/___/ .__\\_,_/\\__/\\__/_/  \\___/_/  \\__/_/  \\__/___/___/");
  main_menu.addMenuBannerLine("   /_/");

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
