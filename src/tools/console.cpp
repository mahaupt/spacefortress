#include "console.hpp"

Console* Console::self = 0;

Console::Console() {
  Console::self = this;

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
  move(Console::self->cursor_x, Console::self->cursor_y);
}
