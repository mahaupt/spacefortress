#pragma once
#include <curses.h>

#include <cmath>
#include <string>
#include <vector>

#include "../tools/console.hpp"
#include "uielement.hpp"

class Menu {
 public:
  Menu();
  ~Menu();
  void addSelectable(UiElement *element);
  void addNonSelectable(UiElement *element);

  void render(ConsoleKey cmd);

 private:
  int selection;
  std::vector<UiElement *> menu_items;
  std::vector<UiElement *> menu_text;

  void processInput(ConsoleKey cmd);
};
