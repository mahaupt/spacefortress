#include "main.hpp"

Game* main_pgame = 0;
bool main_running = true;
MainState main_state = MAIN_MENU;

/**
 * Callbacks
 */
void main_endProgram(void) { main_running = false; }
void main_stopGame(void) { main_state = MAIN_MENU; }
void main_startGame(void) {
  if (main_pgame == 0) return;
  main_state = GAME;
  main_pgame->start();
}

/**
 * This is the main state machine for the program
 * @return 0
 */
int main() {
#ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  //////////////////////////////////////////////
  // MODULE LOADING
  Log log("log.txt", LogLevel::LL_ALL);
  Log::info("start");
  Config config("config.yaml");
  Lang lang;
  Console console;

  //////////////////////////////////////////////
  // MENU SETUP
  Menu main_menu;
  auto main_menu_1 =
      MenuItem(0, -1, Lang::get("general_start_game"), &main_startGame);
  auto main_menu_2 =
      MenuItem(0, 0, Lang::get("general_start_game"), &main_startGame);
  auto main_menu_3 = MenuItem(0, 1, Lang::get("menu_exit"), &main_endProgram);
  main_menu.addSelectable(&main_menu_1);
  main_menu.addSelectable(&main_menu_2);
  main_menu.addSelectable(&main_menu_3);

  Text sf_banner(0, 2, MIDDLE, TOP, LEFT);
  sf_banner.addTextLine("   ____                 ____         __");
  sf_banner.addTextLine(
      "  / _____ ___ ________ / _____  ____/ /________ ___ ___");
  sf_banner.addTextLine(
      " _\\ \\/ _ / _ `/ __/ -_/ _// _ \\/ __/ __/ __/ -_(_-<(_-<");
  sf_banner.addTextLine(
      "/___/ .__\\_,_/\\__/\\__/_/  \\___/_/  \\__/_/  \\__/___/___/");
  sf_banner.addTextLine("   /_/");
  main_menu.addNonSelectable((UiElement*)&sf_banner);

  Text greeting_text(-2, -2, MIDDLE, BOTTOM, LEFT);
  greeting_text.addTextLine("Error: test error");
  main_menu.addNonSelectable((UiElement*)&greeting_text);

  //////////////////////////////////////////////
  // GAME SETUP
  Game game;
  main_pgame = &game;

  //////////////////////////////////////////////
  // MAIN RENDERING LOOP
  ConsoleKey key = ConsoleKey::NONE;
  Console::sclear();
  while (main_running) {
    // render main console
    switch (main_state) {
      case MAIN_MENU: {
        Console::sclear();
        main_menu.render(key);
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
