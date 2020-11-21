#pragma once
#include <ctime>
#include <fstream>

enum LogLevel {
  OFF = 0,
  FATAL = 1,
  ERROR = 2,
  WARN = 3,
  INFO = 4,
  DEBUG = 5,
  TRACE = 6,
  ALL = 7
};

class Logger {
 public:
  Logger(LogLevel log_level = ERROR);
  ~Logger();

  void log(const char* msg, LogLevel level = INFO);
  const char* getLogLevelStr(LogLevel level);

 private:
  std::fstream fs;
  LogLevel log_level;
};
