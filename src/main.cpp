#include "game.hpp"
#include "tools/config.hpp"
#include "tools/console.hpp"
#include "tools/lang.hpp"
#include "tools/log.hpp"
#include "ui/inputtext.hpp"
#include "ui/menu.hpp"
#include "ui/text.hpp"

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
  Log log(ALL);
  Log::info("start");
  Config config;
  Lang lang;
  Console console;

  Menu main_menu;
  main_menu.addMenuEntry(Lang::get("menu_create_crew"), &startGame);
  main_menu.addMenuEntry(Lang::get("menu_join_crew"), &startGame);
  main_menu.addMenuEntry(Lang::get("menu_exit"), &endProgram);

  Text sf_banner(0, 2, MIDDLE, TOP, LEFT);
  sf_banner.addTextLine("   ____                 ____         __");
  sf_banner.addTextLine(
      "  / _____ ___ ________ / _____  ____/ /________ ___ ___");
  sf_banner.addTextLine(
      " _\\ \\/ _ / _ `/ __/ -_/ _// _ \\/ __/ __/ __/ -_(_-<(_-<");
  sf_banner.addTextLine(
      "/___/ .__\\_,_/\\__/\\__/_/  \\___/_/  \\__/_/  \\__/___/___/");
  sf_banner.addTextLine("   /_/");
  main_menu.addMenuText(sf_banner);

  InputText itext;

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

    itext.render(key);

    refresh();

    timeout(100);
    key = console.getKey();

    if (key == KEY_Q) {
      break;
    }
  }

  return 0;
}
