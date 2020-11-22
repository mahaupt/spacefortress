#include "text.hpp"

Text::Text(int x, int y, UiAlignment align_x, UiAlignment align_y,
           UiAlignment align_text)
    : UiElement(x, y, align_x, align_y), text_size(0) {
  this->align_text = align_text;
}

void Text::setPosition(int x, int y, UiAlignment align_x, UiAlignment align_y,
                       UiAlignment align_text) {
  this->setPosition(x, y, align_x, align_y);
  this->align_text = align_text;
}

void Text::addTextLine(std::string line) {
  textlines.push_back(line);
  this->text_size = fmax(line.length(), this->text_size);
}

void Text::render(ConsoleKey key) {
  int start_x, start_y;
  this->calcDrawOffset(start_x, start_y);

  // center middle alignment of y axis with element size
  if (this->align_y == MIDDLE) {
    start_y -= round(this->textlines.size() / 2.0f);
  }

  // render each line
  for (int i = 0; i < this->textlines.size(); i++) {
    int dx = -floor(this->text_size / 2.0f);
    switch (this->align_text) {
      case (MIDDLE):
        dx = -floor(this->textlines[i].length() / 2.0f);
        break;
      case (RIGHT):
        dx = -this->textlines[i].length();
        break;
    }

    mvprintw(start_y + i, start_x + dx, this->textlines[i].c_str());
  }
}
