#pragma once

#include <cmath>
#include <vector>

#include "../../gameobject.hpp"
#include "../../tools/lang.hpp"
#include "program.hpp"

namespace shipos {
class Map : public Program {
 public:
  Map(Ship* ship, std::vector<GameObject*>* game_objects);
  Map(Ship* ship, std::vector<GameObject*>* game_objects,
      WindowAlignment alignment_x, WindowAlignment alignment_y, double size_x,
      double size_y);
  void render(ConsoleKey key);

 private:
  int wwidth;
  int wheight;
  std::vector<GameObject*>* game_objects;

  void getWindowSize();
};
}  // namespace shipos
