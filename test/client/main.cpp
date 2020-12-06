#include <iostream>

#include "../../src/tools/client.hpp"
#include "../../src/tools/log.hpp"

int main(void) {
  Log log(LogLevel::ALL);
  Client c("127.0.0.1", 8123);

  std::cin.get();

  return 0;
}
