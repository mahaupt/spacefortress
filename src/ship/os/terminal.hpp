#pragma once
#include <string>
#include <vector>

#include "../../tools/console.hpp"
#include "../../ui/inputtext.hpp"
#include "program.hpp"

namespace shipos {
class Terminal : public Program {
 public:
  Terminal(WINDOW* win, Ship* ship);
  void setState(ProgramState s);
  void render(ConsoleKey key);

 private:
  std::vector<std::string> terminal_lines;
  InputText input_field;
};
}  // namespace shipos
