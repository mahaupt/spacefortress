#include <iostream>

#include "../sf/tools/client.hpp"
#include "../sf/tools/log.hpp"

int main(void) {
  Log log(LogLevel::LL_ALL);
  Client c("127.0.0.1", 8123);
  if (!c.isConnected()) return 1;
  std::cin.get();

  return 0;
}
