#include "console.hpp"

Console* Console::self = 0;

Console::Console() {
  Console::self = this;

  initscr();
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  this->showCursor(false);
  this->sclear();

  Log::info("console module loaded");
  if (has_colors()) {
    Log::info("console supports colors");
  } else {
    Log::warn("console has no color support");
  }

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
  printw("MIT License - Copyright (c) 2020 Marcel Haupt\n\n");
  printw(Lang::get("menu_press_key").c_str());
  refresh();

  // wait for enter
  getch();
}

/**
 * sets the global cursor position to render the cursor
 * @param x
 * @param y
 */
void Console::setCursorPos(int x, int y) {
  if (Console::self == 0) return;
  Console::self->cursor_x = x;
  Console::self->cursor_y = y;
}

void Console::renderCursor() {
  if (Console::self == 0) return;
  if (!Console::self->show_cursor) return;
  move(Console::self->cursor_x, Console::self->cursor_y);
}

void Console::showCursor(bool show) {
  if (Console::self == 0) return;
  Console::self->show_cursor = show;
  if (show) {
    curs_set(1);
  } else {
    curs_set(0);
  }
};

void Console::initColors() {
  init_pair((short int)ConsoleColor::YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair((short int)ConsoleColor::RED, COLOR_RED, COLOR_BLACK);
}
