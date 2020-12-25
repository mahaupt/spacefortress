#include "../src/sf/tools/vec2.hpp"

#include "testbase.hpp"

int main(int, char**) {
  Vec2 v(1, 5);
  Vec2 w(-9, 3);
  Vec2 x = v - w;

  ALEPH_ASSERT_EQUAL(x.getX(), 10);
  ALEPH_ASSERT_EQUAL(x.getY(), 2);

  return 0;
}
