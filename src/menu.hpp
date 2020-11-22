#pragma once
#include <ncurses.h>

#include <cmath>
#include <string>
#include <vector>

#include "tools/console.hpp"
#include "tools/logger.hpp"

struct MenuEntry {
  std::string name;
  void (*callback)(void);
};

class Menu {
 public:
  Menu();
  ~Menu();
  void addMenuEntry(std::string name, void (*callback)(void) = 0);
  void addMenuBannerLine(std::string line);

  void render(ConsoleKey cmd);

 private:
  int selection;
  int menu_banner_size;
  std::vector<MenuEntry> menu_entries;
  std::vector<std::string> menu_banner;

  void processInput(ConsoleKey cmd);
  void renderMenuItems();
  void renderMenuBanner();
};
