#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

/**
 * @brief Set timestamp for log messages.
 *
 * @return std::string
 */
static std::string timestamp() {
  auto now = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(now);
  std::ostringstream ss;
  // localtime is fine for a single-threaded game logger
  std::tm* tm_info = std::localtime(&t);  // NOLINT(concurrency-mt-unsafe)
  ss << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

/**
 * @brief Construct a new Logger:: Logger object.
 *
 * Opens the log files for writing.
 */
Logger::Logger() {
  logStream.open("game.log", std::ios::trunc);
  errStream.open("error.log", std::ios::app);
}

/**
 * @brief Destroy the Logger::Logger object.
 *
 * Closes the log files if they are open.
 */
Logger::~Logger() {
  if (logStream.is_open()) logStream.close();
  if (errStream.is_open()) errStream.close();
}

/**
 * @brief Get the singleton instance of the Logger.
 *
 * @return Logger&
 */
Logger& Logger::get() {
  static Logger instance;
  return instance;
}

/**
 * @brief Log a message to the general log file.
 *
 * @param msg The message to log.
 */
void Logger::log(const std::string& msg) {
  if (logStream.is_open()) {
    logStream << "[" << timestamp() << "] " << msg << "\n";
    logStream.flush();
  }
}

/**
 * @brief Log an error message to the error log file.
 *
 * @param msg The error message to log.
 */
void Logger::error(const std::string& msg) {
  if (errStream.is_open()) {
    errStream << "[" << timestamp() << "] " << msg << "\n";
    errStream.flush();
  }
}
