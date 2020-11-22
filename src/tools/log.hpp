#pragma once
#include <ctime>
#include <fstream>
#include <string>

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

class Log {
 public:
  Log(LogLevel log_level = ERROR);
  ~Log();

  void olog(std::string msg, LogLevel level = INFO);
  const char* getLogLevelStr(LogLevel level);

  static void log(std::string msg, LogLevel level = INFO);
  static void fatal(std::string msg) { Log::log(msg, FATAL); };
  static void error(std::string msg) { Log::log(msg, ERROR); };
  static void warn(std::string msg) { Log::log(msg, WARN); };
  static void info(std::string msg) { Log::log(msg, INFO); };
  static void debug(std::string msg) { Log::log(msg, DEBUG); };
  static void trace(std::string msg) { Log::log(msg, TRACE); };
  static void all(std::string msg) { Log::log(msg, ALL); };

 private:
  static Log* self;
  std::fstream fs;
  LogLevel log_level;
};
