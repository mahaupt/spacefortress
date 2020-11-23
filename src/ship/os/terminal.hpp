#pragma once
#include <string>
#include <vector>

#include "../../tools/console.hpp"
#include "../../ui/inputtext.hpp"
#include "program.hpp"

namespace shipos {
constexpr unsigned int str2int(const char* str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

class Terminal : public Program {
 public:
  Terminal(WINDOW* win, Ship* ship);
  void setState(ProgramState s);
  void render(ConsoleKey key);
  void processCmd(std::string cmd);

 private:
  std::vector<std::string> terminal_lines;
  InputText input_field;
};
}  // namespace shipos
