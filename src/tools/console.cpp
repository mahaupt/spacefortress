#include "console.hpp"

Console::Console() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  clear();
  this->printBanner();
}

Console::~Console() { endwin(); }

void Console::printBanner() {
  printw("   ____                 ____         __\n");
  printw("  / _____ ___ ________ / _____  ____/ /________ ___ ___\n");
  printw(" _\\ \\/ _ / _ `/ __/ -_/ _// _ \\/ __/ __/ __/ -_(_-<(_-<\n");
  printw("/___/ .__\\_,_/\\__/\\__/_/  \\___/_/  \\__/_/  \\__/___/___/\n");
  printw("   /_/\n");
  printw("#########################################################\n\n");
  printw(Lang::get("menu_intro").c_str());

  printw("\nGitHub: https://github.com/cbacon93/spacefortress\n\n");
  printw(Lang::get("menu_press_key").c_str());
  refresh();

  // wait for enter
  getch();
}
