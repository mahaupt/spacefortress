#include "helm.hpp"

shipos::Helm::Helm(Ship* ship) : Program(ship), autopilot(false) {}

shipos::Helm::Helm(Ship* ship, WindowAlignment alignment_x,
                   WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y),
      autopilot(false) {
  this->window->setTitle(Lang::get("program_helm"));
}

void shipos::Helm::render(ConsoleKey key) {
  werase(this->win);
  this->getWindowSize();

  // get rotation from ship
  this->rot = this->ship->getRot();

  // parse keys
  if ((char)key == 'a' || key == ConsoleKey::ARROW_LEFT) {
    this->rot -= 0.05;
    this->autopilot = false;
  }
  if ((char)key == 'd' || key == ConsoleKey::ARROW_RIGHT) {
    this->rot += 0.05;
    this->autopilot = false;
  }
  if ((char)key == 'w' || key == ConsoleKey::ARROW_UP) {
    // fire engines
    double thr_x = sin(this->rot);
    double thr_y = cos(this->rot);
    this->ship->applyForce(thr_x, thr_y);
    this->autopilot = false;
  }
  if ((char)key == 'y') {
    this->autopilot = true;
  }

  // correct rot variable
  if (this->rot < 0) {
    this->rot += 2 * 3.1416;
  }
  if (this->rot > 2 * 3.1416) {
    this->rot -= 2 * 3.1416;
  }

  // autopilot
  if (this->autopilot) {
    // get vel vector
    double vx;
    double vy;
    this->ship->getVel(vx, vy);

    // calc vel angle
    double ang = atan2(vx, vy);
    // rotate ang + 180°
    if (ang < 3.1416) {
      ang += 3.1416;
    } else {
      ang -= 3.1416;
    }

    double avec = ang - this->rot;
    if (avec > 0) {
      avec = fmin(avec, 0.05);
    } else {
      avec = fmax(avec, -0.05);
    }

    this->rot += avec;

    mvwprintw(this->win, 2, 1, "%.0f", ang / 3.1416 * 180.0);

    // thrust
    if (abs(ang - this->rot) <= 3.1416 / 180.0 / 5.0) {
      double velabs = this->ship->getVelAbs() * 1000.0 * 5;
      velabs = fmin(velabs, 1.0);
      double thr_x = sin(this->rot) * velabs;
      double thr_y = cos(this->rot) * velabs;

      // turn ap off when stopped
      if (velabs <= 0.0001) {
        this->autopilot = false;
      } else {
        this->ship->applyForce(thr_x, thr_y);
      }
    }
  }

  // print angle
  mvwprintw(this->win, 1, 1, "%.0f", this->rot / 3.1416 * 180.0);

  // draw center
  int cx = round(this->wwidth / 2.0f) - 1;
  int cy = round(this->wheight / 2.0f) - 2;
  mvwprintw(this->win, cy, cx, "O");
  double r = fmin((this->wwidth - 4) / 2.0, this->wheight - 6) / 2.0;

  // draw circle
  int steps = round(r * 20);
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
  std::string pwr = Lang::get("program_helm_eng") + ": [";
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
  std::string line1 = "a: " + Lang::get("program_helm_left") +
                      " - b: " + Lang::get("program_helm_right");
  mvwprintw(this->win, this->wheight - 3, 1, line1.c_str());
  std::string line2 = "w: " + Lang::get("program_helm_fwd") + " - y: autostop";
  mvwprintw(this->win, this->wheight - 2, 1, line2.c_str());

  // apply rotation
  this->ship->setRot(this->rot);

  // render window
  Program::render(key);
}

/**
 * saves window dimensions
 * window class clears window for us if resized
 */
void shipos::Helm::getWindowSize() {
  getmaxyx(this->win, this->wheight, this->wwidth);
}
