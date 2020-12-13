#include "client.hpp"

Client::Client(const std::string& address, const unsigned int& port)
    : socket(address, port) {
  if (socket.isConnected()) {
    socket.authenticate();
    socket.startListener();
  }
}

Client::~Client() {
#ifdef WIN32
  //windows cleanup
  WSACleanup();
#endif
  
}
