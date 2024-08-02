#ifndef __LOG_HPP
#define __LOG_HPP

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Yaml {

class Logger {
private:
  static void init() noexcept;

public:
  static std::shared_ptr<spdlog::logger> s_logger;

  static spdlog::logger &get() noexcept;

  Logger() = delete;
  Logger(const Logger &other) = delete;
  Logger(Logger &&other) = delete;
  Logger &operator=(const Logger &other) = delete;
  Logger &operator=(Logger &&other) = delete;
  ~Logger() = delete;
};

} // namespace Yaml

#endif // __LOG_HPP