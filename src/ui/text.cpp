#include "text.hpp"

Text::Text(int x, int y, DisplayAlignment align_x, DisplayAlignment align_y,
           DisplayAlignment align_text)
    : text_size(0) {
  this->setPosition(x, y, align_x, align_y, align_text);
}

void Text::setPosition(int x, int y, DisplayAlignment align_x,
                       DisplayAlignment align_y, DisplayAlignment align_text) {
  this->x = x;
  this->y = y;
  this->align_x = align_x;
  this->align_y = align_y;
  this->align_text = align_text;
}

void Text::addTextLine(std::string line) {
  textlines.push_back(line);
  this->text_size = fmax(line.length(), this->text_size);
}

void Text::render() {
  // calculate anchor x pos
  int start_x = this->x;
  switch (this->align_x) {
    case (MIDDLE):
      start_x = round(COLS / 2.0f) + this->x;
      break;
  }

  // calculate anchor y pos
  int start_y = this->y;
  switch (this->align_y) {
    case (MIDDLE):
      start_y = round(LINES / 2.0f - this->textlines.size() / 2.0f) + this->y;
      break;
    case (BOTTOM):
      start_y = LINES - this->textlines.size() + this->y;
      break;
  }

  // render each line
  for (int i = 0; i < this->textlines.size(); i++) {
    int dx = -floor(this->text_size / 2.0f);
    switch (this->align_text) {
      case (MIDDLE):
        dx = -floor(this->textlines[i].length() / 2.0f);
        break;
    }

    mvprintw(start_y + i, start_x + dx, this->textlines[i].c_str());
  }
}
