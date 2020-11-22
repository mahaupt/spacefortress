#pragma once
#include <fstream>
#include <string>

class Config {
 public:
  Config();
  ~Config();

 private:
  std::fstream fs;
  static Config* self;

  void read();
};
