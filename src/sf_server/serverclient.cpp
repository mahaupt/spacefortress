#include "serverclient.hpp"


ServerClient::ServerClient(SOCKET socket) :
      is_authenticated(false),
      name("guest"),
      connection_time(std::chrono::system_clock::now())
{
  this->isocket = socket;
  this->is_connected = true;
  this->readAddress();

  Log::info("Client connected: " + this->address + ":" + std::to_string(this->port));
}

ServerClient::~ServerClient() {
  Log::info("Client disconnected: " + this->address + ":" + std::to_string(this->port));
}


/**
 * handle client based messages
 * other messages will be transfered to queue where server main queue will handle it
 */
bool ServerClient::handleMsg(std::shared_ptr<NetMsg> &pnmsg) {
  
  //handle message
  switch ((NetMsgType)pnmsg->type) {
    case (NetMsgType::AUTH): {
      if (this->is_authenticated) return false;
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      this->name = std::string(txt->text, pnmsg->size);
      this->is_authenticated = true;
      Log::info(this->address + ": authenticates as " + this->name);
      return false;
    }
    case (NetMsgType::TEXT): {
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      return true;
    }
    default:
      //nothing
      break;
  }
  
  return true;
}


