#include "basesocket.hpp"

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  // Winsock Library
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

BaseSocket::BaseSocket()
    : is_connected(false), isocket(0), ibytes_avbl(0), latency(0) {}

/**
 * disconnects the connection and joins all threads
 * then closes the socket
 */
BaseSocket::~BaseSocket() {
  this->disconnect();

  // join threads
  if (this->fut_listener.valid()) this->fut_listener.wait();

  // close socket
  if (this->isocket > 0) {
    close(this->isocket);
    this->isocket = 0;
  }
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
    size_t bytes = read(this->isocket, buffer_start, free_buffer_size);
    this->ibytes_avbl += bytes;

    if (bytes <= 0) {
      this->disconnect();
      break;
    }

    this->parseiBuffer();
  }
}

/**
 * parses Messages from the buffer and passes it to the message handler functions handleBaseMsg and handleMsg
 * if both of those functions return true, it will be saved into the queue and handled later
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
  send(this->isocket, data, size, 0);
}

void BaseSocket::sendEmptyMsg(const NetMsgType & t) {
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
  if (this->isocket > 0) {
    shutdown(this->isocket, SHUT_RDWR);
  }
}

/**
 * handles low level messages like ping, none, defines uniform behaviour for client & servers
 * specific client or server low-level behaviour can be defined in BaseSocket::handleMsg()
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
