#include <iostream>

#include "../sf/tools/log.hpp"
#include "server.hpp"

int main(void) {
  Log log(LogLevel::LL_ALL);
  Server s("0.0.0.0", 7339);
  if (!s.isSocketReady()) return 1;

  s.start();

  std::cin.get();

  return 0;
}
