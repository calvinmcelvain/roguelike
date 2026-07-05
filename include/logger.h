#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

/**
 * Simple file-based logger for use during ncurses gameplay (stdout is
 * unavailable while ncurses is active).
 *
 * game.log  — truncated each run; use for general debug/info messages.
 * error.log — appended each run; persists errors across sessions.
 *
 * Usage:
 *   LOG("player moved to 5,3");
 *   LOG_ERR("failed to open room file");
 */
class Logger {
 public:
  static Logger& get();

  void log(const std::string& msg);
  void error(const std::string& msg);

 private:
  Logger();
  ~Logger();

  std::ofstream logStream;
  std::ofstream errStream;
};

#define LOG(msg) Logger::get().log(msg)
#define LOG_ERR(msg) Logger::get().error(msg)

#endif
