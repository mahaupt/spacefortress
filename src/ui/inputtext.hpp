#pragma once
#include <cmath>
#include <string>

#include "../tools/console.hpp"
#include "../tools/log.hpp"

/**
 * [render description]
 */
class InputText {
 public:
  InputText();
  void render(ConsoleKey key);

 private:
  std::string label;
  std::string value;

  int cursor_pos;
  int width;

  void processInput(ConsoleKey key);
};
