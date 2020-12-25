#include "clientsocket.hpp"

ClientSocket::ClientSocket() : is_authenticated(false), is_crewmember(false) {}

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
 * Disconnect override extending for resetting authentication behaviour
 */
void ClientSocket::disconnect() {
  BaseSocket::disconnect();
  this->is_authenticated = false;
  this->is_crewmember = false;
  this->prom_ready_for_game = std::promise<bool>();
}

/**
 * Creates Authentification Handshake to server
 * @param username [description]
 * @param crewcode Optional. = "" for creating a crew
 */
void ClientSocket::authenticate(const std::string& username,
                                const std::string& crewcode) {
  NetMsg auth(username.c_str(), NetMsgType::AUTH);

  // create create / join msg depending on crewcode content
  NetMsg intent = (crewcode.length() > 0)
                      ? NetMsg(crewcode.c_str(), NetMsgType::CREW_JOIN)
                      : NetMsg(NetMsgType::CREW_CREATE);

  size_t bytes = auth.writeBuffer(this->obuffer, BS_OBUFFER_SIZE);
  bytes += intent.writeBuffer(this->obuffer + bytes, BS_OBUFFER_SIZE - bytes);
  this->sendData(this->obuffer, bytes);
  Log::debug("client auth request sent");
}

bool ClientSocket::handleMsg(std::shared_ptr<NetMsg>& pnmsg) {
  if (BaseSocket::handleMsg(pnmsg)) return true;
  switch ((NetMsgType)pnmsg->type) {
    case (NetMsgType::AUTHACCEPT): {
      if (!this->is_authenticated) {
        this->is_authenticated = true;
        Log::debug("client authenticated");
      }
      return true;
    }
    case (NetMsgType::AUTHDENY): {
      this->is_authenticated = false;
      this->prom_ready_for_game.set_value(false);
      this->disconnect();
      Log::debug("client auth failed");
      return true;
    }
    case (NetMsgType::ERR_FULL): {
      this->prom_ready_for_game.set_value(false);
      this->disconnect();
      Log::debug("server full");
      return true;
    }
    case (NetMsgType::ERR_CREWNOTFOUND): {
      this->prom_ready_for_game.set_value(false);
      this->disconnect();
      Log::debug("crew code not found");
      return true;
    }
    case (NetMsgType::CREW_ACCEPT): {
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      this->crew_code = std::string(txt->text, pnmsg->size);
      this->is_crewmember = true;
      this->prom_ready_for_game.set_value(true);
      Log::debug("joined crew: " + this->crew_code);
      return true;
    }
    default:
      // nothing
      break;
  }
  return false;
}

/**
 * Get Future from authentication process
 * @return std::future<bool> future authentication result
 */
std::future<bool> ClientSocket::getReadyForGameFuture() {
  return this->prom_ready_for_game.get_future();
}
