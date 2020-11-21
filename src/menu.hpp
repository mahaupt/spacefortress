#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>
#include <vector>

#include "console.hpp"
#include "logger.hpp"

struct MenuEntry {
  std::string name;
  void (*callback)(void);
};

class Menu {
 public:
  Menu();
  ~Menu();
  void addMenuEntry(std::string name, void (*callback)(void) = 0);
  void render(ConsoleKey cmd);
  void processInput(ConsoleKey cmd);

 private:
  int selection;
  std::vector<MenuEntry> menu_entries;
};
