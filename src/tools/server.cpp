#include "server.hpp"

#ifdef WIN32

#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

Server::Server() : isocket(0) {}

Server::~Server() {
  // free up socket
}

bool Server::bind() {
  // create socket
  if ((isocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Log::error("Server socket creation failed");
    return false;
  }

  // attaching socket
  int opt = 1;
  if (setsockopt(isocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(int))) {
    Log::error("Error setting up server");
    return false;
  }

  // setup socket adress
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (::bind(isocket, (struct sockaddr *)&address, sizeof(sockaddr_in)) < 0) {
    Log::error("server socket bind failed");
    return false;
  }
  if (listen(isocket, 5) < 0) {
    Log::error("server listen failed");
    return false;
  }

  return true;
}
