#include "menu.hpp"

Menu::Menu() : selection(0) {}
Menu::~Menu() {}

void Menu::addMenuEntry(std::string name, void (*callback)(void)) {
  MenuEntry me;
  me.name = name;
  me.callback = callback;
  this->menu_entries.push_back(me);
}

void Menu::render(ConsoleKey key) {
  this->processInput(key);
  int start_y = round((LINES - this->menu_entries.size()) / 2.0f) - 1;
  int start_x = round(COLS / 2.0f);

  for (int i = 0; i < this->menu_entries.size(); i++) {
    if (this->selection == i) {
      attrset(A_BOLD);
    }

    int dx = round(this->menu_entries[i].name.length() / 2.0f) + 1;
    mvprintw(start_y + i, start_x - dx, this->menu_entries[i].name.c_str());
    attrset(A_NORMAL);
  }
}

void Menu::processInput(ConsoleKey key) {
  if (key == NONE) return;

  switch (key) {
    case ARROW_UP:
      this->selection--;
      if (this->selection < 0) {
        this->selection = 0;
      }
      break;
    case ARROW_DOWN:
      this->selection++;
      if (this->selection > this->menu_entries.size() - 1) {
        this->selection = this->menu_entries.size() - 1;
      }
      break;
    case ENTER:
      void (*cb)(void) = this->menu_entries[this->selection].callback;
      if (cb != 0) {
        cb();
      }
      break;
  }
}
