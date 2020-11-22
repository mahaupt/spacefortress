#include "log.hpp"

Log* Log::self = 0;

Log::Log(LogLevel log_level) {
  this->log_level = log_level;
  if (log_level != OFF) {
    fs.open("log.txt", std::ios_base::out | std::ios_base::trunc);
  }
  self = this;

  Log::info("log module ready");
}

Log::~Log() {
  if (fs.is_open()) {
    fs.close();
  }
  this->self = 0;
}

void Log::log(std::string msg, LogLevel level) {
  if (Log::self == 0) {
    return;
  }
  Log::self->olog(msg, level);
}

void Log::olog(std::string msg, LogLevel level) {
  // check error levels
  if (level > this->log_level || this->log_level == OFF) {
    return;
  }
  // check fstream open
  if (!fs.is_open()) {
    return;
  }

  // get current time
  time_t now = time(NULL);
  tm now_local = *localtime(&now);

  fs << now_local.tm_year + 1900 << "-";
  fs << now_local.tm_mon + 1 << "-";
  fs << now_local.tm_mday + 1 << "_";
  fs << now_local.tm_hour << ":";
  fs << now_local.tm_min << ":";
  fs << now_local.tm_sec;
  fs << "_[" << this->getLogLevelStr(level) << "]: ";
  fs << msg << std::endl;
  fs.flush();
}

const char* Log::getLogLevelStr(LogLevel level) {
  switch (level) {
    case (FATAL):
      return "FATAL";
    case (ERROR):
      return "ERROR";
    case (WARN):
      return "WARN";
    case (INFO):
      return "INFO";
    case (DEBUG):
      return "DEBUG";
    case (TRACE):
      return "TRACE";
    case (ALL):
      return "ALL";
  }
  return "NONE";
}
