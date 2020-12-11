#include "netmsg.hpp"

#include <cstring>

size_t NetMsg::writeBuffer(char* buffer, size_t buffer_size) {
  if (buffer_size < this->size + NETMSG_HEADER_SIZE) return 0;

  // header
  memcpy(buffer, this, NETMSG_HEADER_SIZE);
  
  // body
  if (this->data != nullptr) {
    memcpy(buffer+NETMSG_HEADER_SIZE, (void*)this->data->getDataPtr(), this->size);
  }
  
  return this->size + NETMSG_HEADER_SIZE;
}


bool NetMsg::tryReadFromBuffer(char* buffer, size_t buffer_size) {
  //get header
  if (buffer_size < NETMSG_HEADER_SIZE) return false;
  memcpy(this, buffer, NETMSG_HEADER_SIZE);
  
  //get body
  if (buffer_size < this->size + NETMSG_HEADER_SIZE) return false;
  char *dataptr = buffer + NETMSG_HEADER_SIZE;
  switch((NetMsgType)this->type) {
    case (NetMsgType::INTENTION_JOIN):
    case (NetMsgType::AUTH):
    case (NetMsgType::TEXT):
      this->data = new NetMsgText(dataptr, this->size);
      break;
    default:
      //nothing
      break;
  }
  
  return true;
}
