#include "game.hpp"
#include "tools/config.hpp"
#include "tools/console.hpp"
#include "tools/lang.hpp"
#include "tools/log.hpp"
#include "ui/inputtext.hpp"
#include "ui/menu.hpp"
#include "ui/menuitem.hpp"
#include "ui/text.hpp"

enum MainState { MAIN_MENU, CREW_CREATE, CREW_JOIN, GAME };

Game* pgame = 0;
bool p_running = true;
MainState main_state = MAIN_MENU;

/**
 * Callbacks
 */
void endProgram(void) { p_running = false; }
void startCrewCreate(void) { main_state = CREW_CREATE; }
void startCrewJoin(void) { main_state = CREW_JOIN; }
void startGame(void) {
  main_state = GAME;
  if (pgame != 0) {
    pgame->start();
  }
}
void stopGame(void) { main_state = MAIN_MENU; }
void backToMenu(void) { main_state = MAIN_MENU; }

/**
 * This is the main state machine for the program
 * @return 0
 */
int main() {
  //////////////////////////////////////////////
  // MODULE LOADING
  Log log("log.txt", LogLevel::LL_ALL);
  Log::info("start");
  Config config;
  Lang lang;
  Console console;

  //////////////////////////////////////////////
  // MENU SETUP
  Menu main_menu;
  auto main_menu_1 = MenuItem(0, -1, Lang::get("menu_create_crew"), &startCrewCreate);
  auto main_menu_2 = MenuItem(0, 0, Lang::get("menu_join_crew"), &startCrewJoin);
  auto main_menu_3 = MenuItem(0, 1, Lang::get("menu_exit"), &endProgram);
  main_menu.addSelectable(&main_menu_1);
  main_menu.addSelectable(&main_menu_2);
  main_menu.addSelectable(&main_menu_3);

  Menu create_menu;
  auto input_username = InputText(-5, -2, Lang::get("general_username") + ": ");
  input_username.setValue(Config::getStr("username", "Steve"));
  auto input_server = InputText(-5, -1, Lang::get("general_server") + ": ");
  input_server.setValue(Config::getStr("server", "127.0.0.1:8123"));
  auto create_menu_1 =
      MenuItem(0, 1, Lang::get("menu_create_crew"), &startGame);
  auto create_menu_2 =
      MenuItem(0, 2, "<< " + Lang::get("general_back"), &backToMenu);
  create_menu.addSelectable(&input_username);
  create_menu.addSelectable(&input_server);
  create_menu.addSelectable(&create_menu_1);
  create_menu.addSelectable(&create_menu_2);

  Menu join_menu;
  auto join_menu_1 = InputText(-5, 0, Lang::get("general_crew_code") + ": ");
  auto join_menu_2 =
      MenuItem(0, 2, Lang::get("general_start_game"), &startGame);
  auto join_menu_3 =
      MenuItem(0, 3, "<< " + Lang::get("general_back"), &backToMenu);
  join_menu.addSelectable(&input_username);
  join_menu.addSelectable(&input_server);
  join_menu.addSelectable(&join_menu_1);
  join_menu.addSelectable(&join_menu_2);
  join_menu.addSelectable(&join_menu_3);

  Text sf_banner(0, 2, MIDDLE, TOP, LEFT);
  sf_banner.addTextLine("   ____                 ____         __");
  sf_banner.addTextLine(
      "  / _____ ___ ________ / _____  ____/ /________ ___ ___");
  sf_banner.addTextLine(
      " _\\ \\/ _ / _ `/ __/ -_/ _// _ \\/ __/ __/ __/ -_(_-<(_-<");
  sf_banner.addTextLine(
      "/___/ .__\\_,_/\\__/\\__/_/  \\___/_/  \\__/_/  \\__/___/___/");
  sf_banner.addTextLine("   /_/");
  main_menu.addNonSelectable(&sf_banner);
  create_menu.addNonSelectable(&sf_banner);
  join_menu.addNonSelectable(&sf_banner);

  //////////////////////////////////////////////
  // GAME SETUP
  Game game;
  pgame = &game;

  //////////////////////////////////////////////
  // MAIN RENDERING LOOP
  ConsoleKey key = ConsoleKey::NONE;
  Console::sclear();
  while (p_running) {
    // render main console
    switch (main_state) {
      case MAIN_MENU: {
        Console::sclear();
        main_menu.render(key);
        break;
      }
      case CREW_CREATE: {
        Console::sclear();
        create_menu.render(key);
        
        //save config
        if (main_state != CREW_CREATE) {
          Config::setStr("username", input_username.getValue());
          Config::setStr("server", input_server.getValue());
          Config::save();
        }
        break;
      }
      case CREW_JOIN: {
        Console::sclear();
        join_menu.render(key);
        
        //save config
        if (main_state != CREW_JOIN) {
          Config::setStr("username", input_username.getValue());
          Config::setStr("server", input_server.getValue());
          Config::save();
        }
        break;
      }
      case GAME:
        game.render(key);
        // state switch
        if (main_state == MAIN_MENU) {
          game.stop();
          Console::showCursor(false);
          Console::sclear();
        }
        break;
    }

    // draw main console
    Console::srefresh();

    // render and draw windows
    if (main_state == GAME) {
      game.renderWin(key);
    }

    // render cursor on top
    Console::renderCursor();

    // keyboard actions
    timeout(100);
    key = console.getKey();
  }
  return 0;
}
