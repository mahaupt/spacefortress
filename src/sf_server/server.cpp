#include "server.hpp"

Server::Server(const std::string& address, const unsigned int& port)
    : socket(address, port), is_running(false) {}

Server::~Server() {
  // try to stop server
  if (this->is_running) {
    this->stop();
  }
  
  // disconnect all clients
  this->clients.clear();
  
#ifdef WIN32
  //windows cleanup
  WSACleanup();
#endif

  Log::info("Server destroy");
}

/**
 * starts server listener threads and accepts clients
 */
void Server::start() {
  Log::info("starting server");
  this->is_running = true;
  this->new_client_acceptor = std::thread(&Server::newClientAcceptor, this);
  this->client_updater = std::thread(&Server::clientUpdater, this);
}

/**
 * stopping all threads by connecting to self and unblocking the accept() call
 * closes the main server socket
 */
void Server::stop() {
  Log::info("stopping server");
  
  // stopping threads
  this->is_running = false;
  this->socket.unblock();
  this->new_client_acceptor.join();
  this->client_updater.join();
}

/**
 * thread handles new clients
 * throws away client when server is full
 */
void Server::newClientAcceptor() {
  Log::info("starting client handler");
  while (this->is_running) {
    auto newclient = this->socket.accept();
    if (!this->is_running) break;
    if (newclient) {
      {
        if (clients.size() >= SERVER_MAX_CLIENTS){
          newclient->sendEmptyMsg(NetMsgType::ERR_FULL);
          continue; // destructs client object
        }
        
        std::lock_guard<std::mutex> guard(this->mx_clients);
        clients.push_back(newclient);
      }

      // start client listener
      newclient->startListener();
    }
  }
  Log::info("stopping client handler");
}

void Server::clientUpdater() {
  Log::info("starting client updater");
  while (this->is_running) {
    this->garbageCollector();
    {
      std::lock_guard<std::mutex> guard(this->mx_clients);
      for (const auto & client : this->clients) {
        //update client latency
        //client->ping();
        
        //parse messages
        while(client->isMsgAvailable())
          msgHandler(client, client->popMessage());
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  Log::info("stopping client updater");
}

/**
 * removes disconnected clients from memory
 */
void Server::garbageCollector() {
  std::lock_guard<std::mutex> guard(this->mx_clients);
  auto it = this->clients.begin();
  while (it != this->clients.end()) {
    // is dead object?
    if (!(*it)->isConnected()) {
      it = this->clients.erase(it);
    } else {
      it++;
    }
  }
}


/**
 * handles client messages on a server level
 * Mostly game and update messages
 */
void Server::msgHandler(const std::shared_ptr<ServerClient> & client, const std::shared_ptr<NetMsg> & pnmsg) {
  if (!client->isAuthenticated()) {
    Log::warn(client->getAddress() + ": client not authenticated!");
    client->sendEmptyMsg(NetMsgType::ERR_REQ);
    client->disconnect();
    return;
  }
  
  switch((NetMsgType)pnmsg->type)
  {
    case(NetMsgType::INTENTION_CREATE): {
      //create new crew
      this->crews.push_back(Crew());
      Log::info(client->getAddress() + ": creates crew");
      client->setCrewmenber(true);
      break;
    }
    case(NetMsgType::INTENTION_JOIN): {
      //join crew
      NetMsgText *text = (NetMsgText*)pnmsg->data;
      std::string crewcode(text->text, pnmsg->size);
      if (!this->tryAddCrewMember(client, crewcode)) {
        client->sendEmptyMsg(NetMsgType::ERR_CREWNOTFOUND);
        client->disconnect();
        break;
      }
      Log::info(client->getAddress() + ": joins crew");
      client->setCrewmenber(true);
      break;
    }
    default:
      //drop message
      break;
  }
}


/**
 * try and add the crewmember to a crew by crew code
 * @return bool true on success, otherwise false
 */
bool Server::tryAddCrewMember(const std::shared_ptr<ServerClient> & client, const std::string &crewcode) {
  Crew *c = findCrewByCode(crewcode);
  if (c == nullptr) return false;
  
  c->crew_members.push_back(client);
  return true;
}

/**
 * searches for crew by crew code
 * @return Crew* the found crew or nullptr
 */
Crew * Server::findCrewByCode(const std::string &code) {
  for(auto &crew : this->crews) {
    if (crew.crew_code == code) {
      return &crew;
    }
  }
  return nullptr;
}
