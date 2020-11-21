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
  printw("    ____                 ____         __\n");
  printw("   / _____ ___ ________ / _____  ____/ /________ ___ ___\n");
  printw("  _\\ \\/ _ / _ `/ __/ -_/ _// _ \\/ __/ __/ __/ -_(_-<(_-<\n");
  printw(" /___/ .__\\_,_/\\__/\\__/_/  \\___/_/  \\__/_/  \\__/___/___/\n");
  printw("    /_/\n");
  printw("#########################################################\n\n");
  printw(
      "Spacefortress is a science fiction command line space ship\n"
      "simulator. The main inspiration for this project comes from the\n"
      "dwarf fortress game. The Project is open source and was created\n"
      "by Marcel Haupt to learn advanced C++ programming.\n\n");

  printw("GitHub: https://github.com/cbacon93/spacefortress\n\n");
  printw("Press any key to continue...");
  refresh();

  // wait for enter
  getch();
}
