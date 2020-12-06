#include <iostream>

#include "../../src/tools/log.hpp"
#include "../../src/tools/server.hpp"
#include "../../src/tools/serversocket.hpp"

int main(void) {
  Log log(LogLevel::ALL);
  Server s(ServerSocket("127.0.0.1", 8123));
  s.start();

  std::cin.get();

  return 0;
}
