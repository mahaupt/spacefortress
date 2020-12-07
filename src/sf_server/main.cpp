#include <iostream>

#include "../sf/tools/log.hpp"
#include "../sf/tools/server.hpp"

int main(void) {
  Log log(LogLevel::ALL);
  Server s("0.0.0.0", 8123);
  if (!s.isSocketReady()) return 1;
  
  s.start();

  std::cin.get();

  return 0;
}
