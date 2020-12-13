#include "log.hpp"

Log* Log::self = 0;

/**
 * Goes to a file
 */
Log::Log(const char* file, const LogLevel& log_level) : fs(nullptr) {
  this->log_level = log_level;
  if (log_level != LogLevel::LL_OFF) {
    fs = new std::fstream(file, std::ios_base::out | std::ios_base::trunc);
  }
  self = this;

  Log::info("log module ready");
}

/**
 * goes to standard output
 */
Log::Log(const LogLevel& log_level) : fs(nullptr) {
  this->log_level = log_level;
  if (log_level != LogLevel::LL_OFF) {
    fs = &std::cout;
  }
  self = this;

  Log::info("log module ready");
}

Log::~Log() {
  if (fs != nullptr) {
    if (fs != &std::cout) {
      if (((std::fstream*)fs)->is_open()) {
        ((std::fstream*)fs)->close();
      }
      delete (std::fstream*)fs;
    }
  }
  this->self = 0;
}

void Log::log(const std::string& msg, const LogLevel& level) {
  if (Log::self == 0) {
    return;
  }
  Log::self->olog(msg, level);
}

void Log::olog(const std::string& msg, const LogLevel& level) {
  std::lock_guard<std::mutex> guard(this->mx_write);

  // check error levels
  if (level > this->log_level || this->log_level == LogLevel::LL_OFF) {
    return;
  }
  // check fstream open
  if (fs == nullptr) {
    return;
  }
  if (fs != &std::cout) {
    if (!((std::fstream*)fs)->is_open()) {
      return;
    }
  }

  // get current time
  time_t now = time(NULL);
  tm now_local = *localtime(&now);

  (*fs) << now_local.tm_year + 1900 << "-";
  (*fs) << now_local.tm_mon + 1 << "-";
  (*fs) << now_local.tm_mday + 1 << "_";
  (*fs) << now_local.tm_hour << ":";
  (*fs) << now_local.tm_min << ":";
  (*fs) << now_local.tm_sec;
  (*fs) << "_[" << this->getLogLevelStr(level) << "]: ";
  (*fs) << msg << std::endl;
  fs->flush();
}

const char* Log::getLogLevelStr(const LogLevel& level) {
  switch (level) {
    case (LogLevel::LL_FATAL):
      return "FATAL";
    case (LogLevel::LL_ERROR):
      return "ERROR";
    case (LogLevel::LL_WARN):
      return "WARN";
    case (LogLevel::LL_INFO):
      return "INFO";
    case (LogLevel::LL_DEBUG):
      return "DEBUG";
    case (LogLevel::LL_TRACE):
      return "TRACE";
    case (LogLevel::LL_ALL):
      return "ALL";
    case (LogLevel::LL_OFF):
      return "ALL";
  }
  return "NONE";
}
