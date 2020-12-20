#include "clientsocket.hpp"

ClientSocket::ClientSocket() : is_authenticated(false) {}

ClientSocket::ClientSocket(const std::string& address, const unsigned int& port)
    : ClientSocket() {
  this->connect(address, port);
}

ClientSocket::~ClientSocket() { Log::info("client socket closed"); }

void ClientSocket::connect(const std::string& address,
                           const unsigned int& port) {
  this->port = port;
  this->address = address;

  // windows WSA
  if (!BaseSocket::initWsa()) return;

  // create socket
  if (!this->createSocketClient()) {
    Log::error("client socket creation failed");
    return;
  }

  Log::info("client socket created");

  this->is_connected = true;
}

/**
 * Creates Authentification Handshake to server
 * @param username [description]
 * @param crewcode Optional. = "" for creating a crew
 */
void ClientSocket::authenticate(const std::string& username,
                                const std::string& crewcode) {
  NetMsg auth(username.c_str());
  auth.setType(NetMsgType::AUTH);

  // create create / join msg depending on crewcode content
  NetMsg intent = (crewcode.length() > 0) ? NetMsg(crewcode.c_str()) : NetMsg();
  intent.setType(NetMsgType::INTENTION_CREATE);
  if (crewcode.length() > 0) {
    intent.setType(NetMsgType::INTENTION_JOIN);
  }

  size_t bytes = auth.writeBuffer(this->obuffer, BS_OBUFFER_SIZE);
  bytes += intent.writeBuffer(this->obuffer + bytes, BS_OBUFFER_SIZE - bytes);
  this->sendData(this->obuffer, bytes);
}

bool ClientSocket::handleMsg(std::shared_ptr<NetMsg>& pnmsg) {
  if (BaseSocket::handleMsg(pnmsg)) return true;
  switch ((NetMsgType)pnmsg->type) {
    case (NetMsgType::AUTHACCEPT): {
      if (!this->is_authenticated) {
        this->is_authenticated = true;
      }
      break;
    }
    case (NetMsgType::AUTHDENY): {
      this->disconnect();
      this->is_authenticated = false;
      break;
    }
    default:
      // nothing
      break;
  }

  return false;
}
