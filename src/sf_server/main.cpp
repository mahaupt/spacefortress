#include <iostream>

#include "../sf/tools/config.hpp"
#include "../sf/tools/log.hpp"
#include "server.hpp"

int main(void) {
  Log log(LogLevel::LL_ALL);
  Config config("server.yaml");
  Server s(Config::getStr("ip", "127.0.0.1"),
           (unsigned int)Config::get<int>("port", 7339));
  if (!s.isSocketReady()) return 1;

  s.start();

  std::cin.get();

  return 0;
}
