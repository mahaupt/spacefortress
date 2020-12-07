#include <iostream>

#include "../sf/tools/log.hpp"
#include "../sf/tools/server.hpp"

int main(void) {
  Log log("log_server.txt", LogLevel::ALL);
  Server s("0.0.0.0", 8123);
  s.start();

  std::cout << "Server started...";
  std::cin.get();

  return 0;
}
