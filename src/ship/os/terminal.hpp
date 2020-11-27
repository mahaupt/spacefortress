#pragma once
#include <string>
#include <vector>

#include "../../tools/console.hpp"
#include "../../tools/lang.hpp"
#include "../../ui/inputtext.hpp"
#include "../modules/dockingport.hpp"
#include "helm.hpp"
#include "map.hpp"
#include "program.hpp"
#include "statusmonitor.hpp"

namespace shipos {
constexpr unsigned int str2int(const char* str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

class Terminal : public Program {
 public:
  Terminal(Ship* ship, std::vector<shipos::Program*>* pprograms);
  Terminal(Ship* ship, std::vector<shipos::Program*>* pprograms,
           WindowAlignment alignment_x, WindowAlignment alignment_y,
           double size_x, double size_y);
  void setState(ProgramState s);
  void render(ConsoleKey key);
  void processCmd(std::string cmd);

 private:
  std::vector<std::string> terminal_lines;
  InputText input_field;
  std::vector<shipos::Program*>* pprograms;

  void setup();
};
}  // namespace shipos
