#include <iostream>

#include "../sf/tools/client.hpp"
#include "../sf/tools/log.hpp"

int main(void) {
  Log log("log_client.txt", LogLevel::ALL);
  Client c("127.0.0.1", 8123);

  std::cout << "Client started...";
  std::cin.get();

  return 0;
}
