#include "netmsg.hpp"

#include <cstring>

size_t NetMsg::writeBuffer(void* buffer, size_t buffer_size) {
  if (buffer_size < this->size + NETMSG_HEADER_SIZE) return 0;

  // header
  memcpy(buffer, this, NETMSG_HEADER_SIZE);
  // body
  void* body = static_cast<char*>(buffer) + NETMSG_HEADER_SIZE;
  memcpy(body, this->data, this->size);
  return this->size + NETMSG_HEADER_SIZE;
}

NetMsg::NetMsg(const NetMsgObject& o) {
  this->type = 1;
  this->size = sizeof(NetMsgObject);
  this->data = (char*)&o;
}
