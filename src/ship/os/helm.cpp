#include "helm.hpp"

shipos::Helm::Helm(WINDOW* win, Ship* ship) : Program(win, ship) {
  this->rot = 0;
}

void shipos::Helm::render(ConsoleKey key) {
  werase(this->win);
  this->getWindowSize();
  if ((char)key == 'a') {
    rot -= 0.01;
  }
  if ((char)key == 'd') {
    rot += 0.01;
  }

  // draw center
  int cx = round(this->wwidth / 2.0f) - 1;
  int cy = round(this->wheight / 2.0f) - 2;
  mvwprintw(this->win, cy, cx, "O");
  double r = fmin((this->wwidth - 4) / 2.0, this->wheight - 6) / 2.0;

  // draw circle
  int steps = round(r * 10);
  for (int i = 0; i < steps; i++) {
    int px = round(sin((double)i + 3.1416 * 2 / (double)steps) * r * 2 + cx);
    int py = round(-cos((double)i + 3.1416 * 2 / (double)steps) * r + cy);
    mvwprintw(this->win, py, px, "X");
  }
  // draw line
  int stepsl = round(r);
  for (int i = 0; i < stepsl; i++) {
    int px =
        round(sin(this->rot) * r * 2.0 * ((double)i / (double)stepsl) + cx);
    int py = round(-cos(this->rot) * r * ((double)i / (double)stepsl) + cy);
    mvwprintw(this->win, py, px, "o");
  }

  // draw eng power
  std::string pwr = "ENG: [";
  int nsymb = this->wwidth - 3 - pwr.length();
  for (int i = 0; i < nsymb - 2; i++) {
    pwr += "#";
  }
  pwr += "__]";
  mvwprintw(this->win, this->wheight - 4, 1, pwr.c_str());
  wattron(this->win, A_BOLD);
  mvwprintw(this->win, this->wheight - 4, cx + 1, "80%%");
  wattroff(this->win, A_BOLD);

  // draw instructions
  mvwprintw(this->win, this->wheight - 3, 1, "a: left - b: right");
  mvwprintw(this->win, this->wheight - 2, 1, "w: fwd");
}

/**
 * saves window dimensions
 * window class clears window for us if resized
 */
void shipos::Helm::getWindowSize() {
  getmaxyx(this->win, this->wheight, this->wwidth);
}
