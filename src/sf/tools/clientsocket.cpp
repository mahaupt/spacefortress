#include "clientsocket.hpp"


ClientSocket::ClientSocket(const std::string& address,
                           const unsigned int& port) {
  this->port = port;
  this->address = address;
  
  //windows WSA
  if (!BaseSocket::initWsa()) return;

  // create socket
  if (!this->createSocketClient()) {
    Log::error("client socket creation failed");
    return;
  }

  

  Log::info("client socket created");

  this->is_connected = true;
}

void ClientSocket::authenticate() {
  NetMsg auth("cbacon");
  auth.setType(NetMsgType::AUTH);
  
  NetMsg intent("abc-def");
  intent.setType(NetMsgType::INTENTION_JOIN);

  size_t bytes = auth.writeBuffer(this->obuffer, BS_OBUFFER_SIZE);
  bytes += intent.writeBuffer(this->obuffer + bytes, BS_OBUFFER_SIZE - bytes);
  this->sendData(this->obuffer, bytes);
}

ClientSocket::~ClientSocket() { Log::info("client socket closed"); }
