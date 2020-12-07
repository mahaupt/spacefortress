#pragma once

#include <cstdint>
#include <cstddef>

#define NETMSG_HEADER_SIZE 5

class NetMsgObject;
enum class NetMsgType { NONE = 0, PING = 1, TEXT = 10, OBJECT = 11 };

class NetMsg {
 public:
  uint8_t type;
  uint32_t size;
  char* data;

  NetMsg() {}
  NetMsg(const NetMsgObject& o);
  size_t writeBuffer(void* buffer, size_t buffer_size);
};

// 81 bytes
class NetMsgObject {
  uint8_t type;
  double x;
  double y;
  double vel_x;
  double vel_y;
  double hull;
  double shield;
  char name[32];
};
