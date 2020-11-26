#include "terminal.hpp"

shipos::Terminal::Terminal(Ship* ship) : Program(ship), input_field(0, 0, "") {
  this->setup();
}

shipos::Terminal::Terminal(Ship* ship, WindowAlignment alignment_x,
                           WindowAlignment alignment_y, double size_x,
                           double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y),
      input_field(0, 0, "") {
  this->window->setTitle(Lang::get("program_terminal"));
  this->setup();
}

void shipos::Terminal::setup() {
  terminal_lines.push_back("ShipOS " + Lang::get("program_terminal"));

  this->input_field.setWin(win);
  this->input_field.setPosition(0, 0, TOP, LEFT);
  this->input_field.setFiller("");
  this->input_field.setSelected(true);

  // activate right away
  Console::showCursor(true);
}

void shipos::Terminal::render(ConsoleKey key) {
  // enter - get value and process input
  if (key == ConsoleKey::ENTER) {
    std::string cmd = input_field.getValue();
    input_field.setValue("");
    this->processCmd(cmd);
  }

  // render text line
  size_t i;
  for (i = 0; i < this->terminal_lines.size(); i++) {
    mvwprintw(this->win, 1 + i, 1, this->terminal_lines[i].c_str());
  }

  // clear and reprint text field
  wmove(this->win, 1 + i, 0);
  wclrtoeol(this->win);
  mvwprintw(this->win, 1 + i, 1, "$ ");
  input_field.setPosition(3, i + 1);
  input_field.render(key);

  // render window
  Program::render(key);
}

/**
 * Disable crsor when Program is HALT oder TERM
 * @param s ProgramState
 */
void shipos::Terminal::setState(ProgramState s) {
  this->state = s;
  if (s == shipos::ProgramState::RUN) {
    input_field.setSelected(true);
    Console::showCursor(true);
  } else {
    input_field.setSelected(false);
    Console::showCursor(false);
  }
}

void shipos::Terminal::processCmd(std::string cmd) {
  terminal_lines.push_back("$ " + cmd);

  if (cmd.length() > 0) {
    // process command
    switch (str2int(cmd.c_str())) {
      case str2int("help"): {
        terminal_lines.push_back(Lang::get("program_terminal_help"));
        terminal_lines.push_back(
            "help, exit, dock, modules, clear, online, offline, killall, nav");
        break;
      }
      case str2int("exit"): {
        if (this->win != stdscr) {
          this->setState(ProgramState::TERM);
        } else {
          terminal_lines.push_back(Lang::get("program_terminal_exit"));
        }
        break;
      }
      case str2int("dock"): {
        // get dock module
        Dockingport* ptr_dp = 0;
        for (const auto& module : *(this->ship->getModules())) {
          if (module->getType() == "Dockingport") {
            ptr_dp = (Dockingport*)module;
            break;
          }
        }
        if (ptr_dp != 0) {
          if (ptr_dp->canDock()) {
            ptr_dp->dock();
            terminal_lines.push_back(Lang::get("program_terminal_docking"));
          } else {
            terminal_lines.push_back(
                Lang::get("program_terminal_dockingerror"));
          }
        } else {
          terminal_lines.push_back(
              Lang::get("program_terminal_nodockingmodule"));
        }

        break;
      }
      case str2int("modules"): {
        size_t i = 0;
        for (const auto& module : *(this->ship->getModules())) {
          std::string line = std::to_string(i++);
          while (line.length() < 4) {
            line += " ";
          }

          line += module->getName();
          while (line.length() < 40) {
            line += " ";
          }
          line += (module->isOnline() ? "online" : "offline");

          terminal_lines.push_back(line);
        }
        break;
      }
      case str2int("clear"): {
        werase(this->win);
        terminal_lines.clear();
        break;
      }
      case str2int("online"): {
        terminal_lines.push_back(Lang::get("program_terminal_turnonline"));
        for (const auto& module : *(this->ship->getModules())) {
          module->setOnline(true);
        }
        break;
      }
      case str2int("offline"): {
        terminal_lines.push_back(Lang::get("program_terminal_turnoffline"));
        for (const auto& module : *(this->ship->getModules())) {
          module->setOnline(false);
        }
        break;
      }
      default:
        terminal_lines.push_back(cmd + ": " +
                                 Lang::get("program_terminal_notfound"));
        break;
    }
  }

  // crop text lines
  int winx;
  int winy;
  getmaxyx(this->win, winy, winx);
  winy -= 3;
  while (terminal_lines.size() > (size_t)winy) {
    terminal_lines.erase(terminal_lines.begin());
  }
}
