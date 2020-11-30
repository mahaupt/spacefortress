#pragma once

#ifdef WIN32

#else
#include <sys/socket.h>
#endif

class Server {
 public:
  Server();
  ~Server();
  void bind();

 private:
  int isocket;
};
