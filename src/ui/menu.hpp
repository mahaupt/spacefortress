#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>
#include <vector>

#include "../tools/console.hpp"
#include "text.hpp"

struct MenuEntry {
  std::string name;
  void (*callback)(void);
};

class Menu {
 public:
  Menu();
  ~Menu();
  void addMenuEntry(std::string name, void (*callback)(void) = 0);
  void addMenuText(Text text);

  void render(ConsoleKey cmd);

 private:
  int selection;
  int menu_banner_size;
  std::vector<MenuEntry> menu_entries;
  std::vector<Text> menu_text;

  void processInput(ConsoleKey cmd);
  void renderMenuItems();
  void renderMenuText();
};
