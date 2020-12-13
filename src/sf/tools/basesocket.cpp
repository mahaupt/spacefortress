#include "basesocket.hpp"

BaseSocket::BaseSocket()
    : isocket(INVALID_SOCKET),
      is_connected(false),
      ibytes_avbl(0),
      latency(0) {}

/**
 * disconnects the connection and joins all threads
 * then closes the socket
 */
BaseSocket::~BaseSocket() {
  this->disconnect();

  // join threads
  if (this->fut_listener.valid()) this->fut_listener.wait();

  // close socket
  if (this->isocket != INVALID_SOCKET) {
    close(this->isocket);
    this->isocket = INVALID_SOCKET;
  }
}

/**
 * Winsock WSA Functionality initializator
 */
bool BaseSocket::wsa_initialized = false;
bool BaseSocket::wsa_result = false;
bool BaseSocket::initWsa() {
  if (BaseSocket::wsa_initialized) return BaseSocket::wsa_result;
  BaseSocket::wsa_initialized = true;

#ifdef WIN32
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    Log::error("WSAStartup failed");
    return false;
  }
#endif
  BaseSocket::wsa_result = true;
  return BaseSocket::wsa_result;
}

/**
 * creates a socket
 */
bool BaseSocket::createSocketClient() {
#ifdef WIN32
  struct addrinfo *result = NULL, *ptr = NULL, hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if (getaddrinfo(this->address.c_str(), std::to_string(this->port).c_str(),
                  &hints, &result) != 0) {
    Log::error("client socket getaddrinfo failed");
    return false;
  }

  ptr = result;
  this->isocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
  if (this->isocket == INVALID_SOCKET) {
    Log::error("client socket creation failed");
    freeaddrinfo(result);
    return false;
  }

  if (connect(this->isocket, ptr->ai_addr, (int)ptr->ai_addrlen) ==
      SOCKET_ERROR) {
    Log::error("client socket connect failed");
    freeaddrinfo(result);
    return false;
  }

#else

  if ((this->isocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Log::error("client socket creation failed");
    return false;
  }

  // setup socket adress
  struct sockaddr_in oaddress;
  oaddress.sin_family = AF_INET;
  oaddress.sin_port = htons(8080);
  inet_aton(this->address.c_str(), &oaddress.sin_addr);

  if (connect(isocket, (struct sockaddr*)&oaddress, sizeof(sockaddr_in)) < 0) {
    Log::error("client socket connect failed");
    return false;
  }
#endif

  return true;
}

/**
 * creates and binds a server socket
 */
bool BaseSocket::createSocketServer() {
#ifdef WIN32
  struct addrinfo *result = NULL, *ptr = NULL, hints;
  memset(&hints, 0, sizeof(addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(this->address.c_str(), std::to_string(this->port).c_str(),
                  &hints, &result) != 0) {
    Log::error("server socket getaddrinfo failed");
    return false;
  }

  this->isocket =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (this->isocket == INVALID_SOCKET) {
    Log::error("server socket creation failed");
    freeaddrinfo(result);
    return false;
  }

  if (bind(this->isocket, result->ai_addr, (int)result->ai_addrlen) ==
      SOCKET_ERROR) {
    freeaddrinfo(result);
    Log::error("server socket bind failed");
    return false;
  }

  if (listen(this->isocket, 5) == SOCKET_ERROR) {
    Log::error("server socket listen failed");
    return false;
  }

#else
  if ((this->isocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Log::error("server socket creation failed");
    return false;
  }

  // setup socket adress
  struct sockaddr_in oaddress;
  oaddress.sin_family = AF_INET;
  oaddress.sin_port = htons(8080);
  inet_aton(this->address.c_str(), &oaddress.sin_addr);

  if (::bind(isocket, (struct sockaddr*)&oaddress, sizeof(sockaddr_in)) < 0) {
    Log::error("server socket bind failed");
    return false;
  }
  if (listen(isocket, 5) < 0) {
    Log::error("server socket listen failed");
    return false;
  }
#endif

  return true;
}

/**
 * starts the listener into a thread pool with async
 * todo: check if this is really executing all client listeners
 */
void BaseSocket::startListener() {
  this->fut_listener =
      std::async(std::launch::async, &BaseSocket::listener, this);
}

/**
 * listens to the socket and saves bytes into the ibuffer
 * calls parseiBuffer() to parse messages out of the buffer
 */
void BaseSocket::listener() {
  while (this->isConnected()) {
    size_t free_buffer_size = BS_IBUFFER_SIZE - this->ibytes_avbl;
    void* buffer_start = this->ibuffer + this->ibytes_avbl;

#ifdef WIN32
    size_t bytes = recv(this->isocket, buffer_start, free_buffer_size, 0);
#else
    size_t bytes = read(this->isocket, buffer_start, free_buffer_size);
#endif

    this->ibytes_avbl += bytes;

    if (bytes <= 0) {
      this->disconnect();
      break;
    }

    this->parseiBuffer();
  }
}

/**
 * parses Messages from the buffer and passes it to the message handler
 * functions handleBaseMsg and handleMsg if both of those functions return true,
 * it will be saved into the queue and handled later
 */
void BaseSocket::parseiBuffer() {
  while (this->ibytes_avbl >= NETMSG_HEADER_SIZE) {
    // get message
    std::shared_ptr<NetMsg> pnmsg = std::make_shared<NetMsg>();
    if (!pnmsg->tryReadFromBuffer(this->ibuffer, this->ibytes_avbl)) {
      break;
    }

    // shift buffer
    size_t bytes_taken = pnmsg->getSize();
    size_t bytes_remaining_in_buffer = this->ibytes_avbl - bytes_taken;
    memmove(this->ibuffer, this->ibuffer + bytes_taken,
            bytes_remaining_in_buffer);
    this->ibytes_avbl -= bytes_taken;

    // handle messages directly
    if (!this->handleBaseMsg(pnmsg)) continue;
    if (!this->handleMsg(pnmsg)) continue;

    // otherwise, put in queue to handle later
    std::lock_guard<std::mutex> lock_guard(mx_inc_msg);
    if (inc_msg.size() > BS_MSG_QUEUE_SIZE) {
      Log::error(address + " msg queue overflow");
      continue;
    }
    inc_msg.push(pnmsg);
  }

  // buffer full - error
  if (this->ibytes_avbl == BS_IBUFFER_SIZE) {
    Log::error("Buffer overflow: " + address);
    this->ibytes_avbl = 0;
  }
}

void BaseSocket::sendData(void* data, size_t size) {
  std::lock_guard<std::mutex> lock_guard(this->mx_socket_tx);
#ifdef WIN32
  send(this->isocket, (const char*)data, size, 0);
#else
  send(this->isocket, data, size, 0);
#endif
}

void BaseSocket::sendEmptyMsg(const NetMsgType& t) {
  NetMsg nmsg(t);
  this->sendData(&nmsg, nmsg.getSize());
}

void BaseSocket::ping() {
  last_ping_sendtime = std::chrono::steady_clock::now();
  this->sendEmptyMsg(NetMsgType::PING);
}

bool BaseSocket::isConnected() { return this->is_connected; }

void BaseSocket::disconnect() {
  this->is_connected = false;

  // disconnect
  if (this->isocket != INVALID_SOCKET) {
    shutdown(this->isocket, SHUT_RDWR);
  }
}

/**
 * handles low level messages like ping, none, defines uniform behaviour for
 * client & servers specific client or server low-level behaviour can be defined
 * in BaseSocket::handleMsg()
 */
bool BaseSocket::handleBaseMsg(std::shared_ptr<NetMsg>& pnmsg) {
  // handle basic behaviour
  switch ((NetMsgType)pnmsg->type) {
    case (NetMsgType::PING): {
      NetMsg reply;
      reply.setType(NetMsgType::PONG);
      this->sendData(&reply, reply.getSize());
      return false;
    }
    case (NetMsgType::PONG): {
      // handle pong
      auto t2 = std::chrono::steady_clock::now();
      auto time_span =
          std::chrono::duration_cast<std::chrono::duration<double>>(
              t2 - this->last_ping_sendtime);
      this->latency = time_span.count() / 2.0;
      if (this->latency > 20) {
        this->latency = 0;
      }
      return false;
    }
    default:
      return true;
  }
}

/**
 * returns true if a message is in queue, otherwise false
 */
bool BaseSocket::isMsgAvailable() {
  std::lock_guard<std::mutex> lock_guard(mx_inc_msg);
  return inc_msg.size() > 0;
}

/**
 * pops the first message from the mesage queue and returns it
 */
std::shared_ptr<NetMsg> BaseSocket::popMessage() {
  std::lock_guard<std::mutex> lock_guard(mx_inc_msg);
  std::shared_ptr<NetMsg> ptr = inc_msg.front();
  inc_msg.pop();
  return ptr;
}

void BaseSocket::readAddress() {
  struct sockaddr_in address;
  size_t addrlen = sizeof(sockaddr_in);
  getpeername(isocket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
  this->address = inet_ntoa(address.sin_addr);
  this->port = ntohs(address.sin_port);
}

SOCKET BaseSocket::accept() {
  SOCKET new_socket;

#ifdef WIN32
  new_socket = ::accept(this->isocket, NULL, NULL);
#else
  struct sockaddr_in iaddress;
  if ((new_socket = ::accept(this->isocket, (struct sockaddr*)&iaddress,
                             (socklen_t*)&iaddress)) < 0) {
    return INVALID_SOCKET;
  }
#endif

  return new_socket;
}
