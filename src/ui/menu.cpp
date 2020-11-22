#include "menu.hpp"

Menu::Menu() : selection(0), menu_banner_size(0) {}
Menu::~Menu() {}

void Menu::addMenuEntry(std::string name, void (*callback)(void)) {
  MenuEntry me;
  me.name = name;
  me.callback = callback;
  this->menu_entries.push_back(me);
}

void Menu::addMenuText(Text text) { this->menu_text.push_back(text); }

/**
 * Renders the menu screen
 * @param key pressed Key to process user input
 */
void Menu::render(ConsoleKey key) {
  this->processInput(key);
  this->renderMenuText();
  this->renderMenuItems();
}

/**
 * renders the menu banner
 */
void Menu::renderMenuText() {
  for (int i = 0; i < this->menu_text.size(); i++) {
    menu_text[i].render();
  }
}

/**
 * renders the menu items
 */
void Menu::renderMenuItems() {
  int start_y = round(LINES / 2.0f - this->menu_entries.size() / 2.0f);
  int start_x = round(COLS / 2.0f);

  for (int i = 0; i < this->menu_entries.size(); i++) {
    if (this->selection == i) {
      attrset(A_BOLD);
    }

    int dx = floor(this->menu_entries[i].name.length() / 2.0f);
    mvprintw(start_y + i, start_x - dx, this->menu_entries[i].name.c_str());
    attrset(A_NORMAL);
  }
}

/**
 * Processes user key input for the menu screen
 * @param ConsoleKey key pressed user key
 */
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