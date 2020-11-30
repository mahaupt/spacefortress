#pragma once

#include "log.hpp"

class Server {
 public:
  Server();
  ~Server();
  bool bind();

 private:
  int isocket;
};
