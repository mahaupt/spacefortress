#include "game.hpp"
#include "tools/config.hpp"
#include "tools/console.hpp"
#include "tools/lang.hpp"
#include "tools/log.hpp"
#include "ui/inputtext.hpp"
#include "ui/menu.hpp"
#include "ui/text.hpp"

enum MainState { MAIN_MENU, CREW_CREATE, CREW_JOIN, GAME };

bool p_running = true;
MainState main_state = MAIN_MENU;

/**
 * Callbacks
 */
void endProgram(void) { p_running = false; }
void startCrewCreate(void) { main_state = CREW_CREATE; }
void startCrewJoin(void) { main_state = CREW_JOIN; }
void startGame(void) { main_state = GAME; }
void backToMenu(void) { main_state = MAIN_MENU; }

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
  main_menu.addMenuEntry(Lang::get("menu_create_crew"), &startCrewCreate);
  main_menu.addMenuEntry(Lang::get("menu_join_crew"), &startCrewJoin);
  main_menu.addMenuEntry(Lang::get("menu_exit"), &endProgram);

  Menu create_menu;
  create_menu.addMenuEntry("Username", &startGame);
  create_menu.addMenuEntry("Server", &startGame);
  create_menu.addMenuEntry("Create Crew", &startGame);
  create_menu.addMenuEntry("<< Back", &backToMenu);

  Menu join_menu;
  join_menu.addMenuEntry("Username", &startGame);
  join_menu.addMenuEntry("Server", &startGame);
  join_menu.addMenuEntry("Crew Code", &startGame);
  join_menu.addMenuEntry("Start Game", &startGame);
  join_menu.addMenuEntry("<< Back", &backToMenu);

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

  Game game;

  ConsoleKey key = NONE;
  while (p_running) {
    clear();

    switch (main_state) {
      case MAIN_MENU:
        main_menu.render(key);
        break;
      case CREW_CREATE:
        create_menu.render(key);
        break;
      case CREW_JOIN:
        join_menu.render(key);
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
