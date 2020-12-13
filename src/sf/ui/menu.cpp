#include "menu.hpp"

Menu::Menu() : selection(-1) {}
Menu::~Menu() {}

void Menu::addSelectable(UiElement *element) {
  this->menu_items.push_back(element);
}

void Menu::addNonSelectable(UiElement *element) {
  this->menu_text.push_back(element);
}

/**
 * Renders the menu screen
 * @param key pressed Key to process user input
 */
void Menu::render(ConsoleKey key) {
  this->processInput(key);

  // init selection
  if (this->selection < 0) {
    this->selection = 0;
    this->menu_items[0]->beforeFocus();
  }

  // render text
  for (int i = 0; i < (int)this->menu_text.size(); i++) {
    menu_text[i]->render(key);
  }

  // render selectable items
  for (int i = 0; i < (int)this->menu_items.size(); i++) {
    menu_items[i]->render(key);
  }
}

/**
 * Processes user key input for the menu screen
 * @param ConsoleKey key pressed user key
 */
void Menu::processInput(ConsoleKey key) {
  if (key == ConsoleKey::NONE) return;

  switch (key) {
    case ConsoleKey::ARROW_UP:
      if (this->selection > 0) {
        this->menu_items[this->selection]->afterFocus();
        this->menu_items[--this->selection]->beforeFocus();
      }
      break;
    case ConsoleKey::ARROW_DOWN:
      if (this->selection < (int)this->menu_items.size() - 1) {
        this->menu_items[this->selection]->afterFocus();
        this->menu_items[++this->selection]->beforeFocus();
      }
      break;
    case ConsoleKey::ENTER:
      this->menu_items[this->selection]->onSelection();
      break;
    default:
      // do nothing
      break;
  }
}
