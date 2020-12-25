#include "main.hpp"

Game* main_pgame = 0;
bool main_running = true;
MainState main_state = MAIN_MENU;
std::string main_crew_code = std::string();
std::string main_serverip = std::string();
std::string main_username = std::string();
std::string main_error = std::string();

/**
 * Callbacks
 */
void main_endProgram(void) { main_running = false; }
void main_startCrewCreate(void) { main_state = CREW_CREATE; }
void main_startCrewJoin(void) { main_state = CREW_JOIN; }
void main_stopGame(void) { main_state = MAIN_MENU; }
void main_backToMenu(void) {
  main_state = MAIN_MENU;
  main_setError("");
}
void main_startGameCreate(void) {
  main_setError("");
  if (main_pgame == 0) return;
  if (main_pgame->connect(main_serverip, main_username, "")) {
    main_state = GAME;
    main_pgame->start();
  }
}
void main_startGameJoin(void) {
  main_setError("");
  if (main_pgame == 0) return;
  if (main_pgame->connect(main_serverip, main_username, main_crew_code)) {
    main_state = GAME;
    main_pgame->start();
  }
}
void main_setError(const char* error) { main_error = error; }

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
      MenuItem(0, -1, Lang::get("menu_create_crew"), &main_startCrewCreate);
  auto main_menu_2 =
      MenuItem(0, 0, Lang::get("menu_join_crew"), &main_startCrewJoin);
  auto main_menu_3 = MenuItem(0, 1, Lang::get("menu_exit"), &main_endProgram);
  main_menu.addSelectable(&main_menu_1);
  main_menu.addSelectable(&main_menu_2);
  main_menu.addSelectable(&main_menu_3);

  Menu create_menu;
  auto input_username = InputText(-5, -2, Lang::get("general_username") + ": ");
  input_username.setValue(Config::getStr("username", "Steve"));
  auto input_server = InputText(-5, -1, Lang::get("general_server") + ": ");
  input_server.setValue(Config::getStr("server", "127.0.0.1:7339"));
  auto create_menu_1 =
      MenuItem(0, 1, Lang::get("menu_create_crew"), &main_startGameCreate);
  auto create_menu_2 =
      MenuItem(0, 2, "<< " + Lang::get("general_back"), &main_backToMenu);
  create_menu.addSelectable(&input_username);
  create_menu.addSelectable(&input_server);
  create_menu.addSelectable(&create_menu_1);
  create_menu.addSelectable(&create_menu_2);

  Menu join_menu;
  auto join_menu_1 = InputText(-5, 0, Lang::get("general_crew_code") + ": ");
  auto join_menu_2 =
      MenuItem(0, 2, Lang::get("general_start_game"), &main_startGameJoin);
  auto join_menu_3 =
      MenuItem(0, 3, "<< " + Lang::get("general_back"), &main_backToMenu);
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
  main_menu.addNonSelectable((UiElement*)&sf_banner);
  create_menu.addNonSelectable((UiElement*)&sf_banner);
  join_menu.addNonSelectable((UiElement*)&sf_banner);

  Text text_error(-2, -2, MIDDLE, BOTTOM, LEFT);
  text_error.addTextLine("Error: test error");
  main_menu.addNonSelectable((UiElement*)&text_error);
  create_menu.addNonSelectable((UiElement*)&text_error);
  join_menu.addNonSelectable((UiElement*)&text_error);

  //////////////////////////////////////////////
  // GAME SETUP
  Game game;
  main_pgame = &game;

  //////////////////////////////////////////////
  // MAIN RENDERING LOOP
  ConsoleKey key = ConsoleKey::NONE;
  Console::sclear();
  while (main_running) {
    // update error
    text_error.setTextLine(0, main_error);

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

        // save input value entries
        main_serverip = input_server.getValue();
        main_username = input_username.getValue();
        main_crew_code = join_menu_1.getValue();

        // save config
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

        // save input value entries
        main_serverip = input_server.getValue();
        main_username = input_username.getValue();
        main_crew_code = join_menu_1.getValue();

        // save config
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
