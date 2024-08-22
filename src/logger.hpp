#ifndef __LOG_HPP
#define __LOG_HPP

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Yaml {

class Logger {
private:
public:
  static std::shared_ptr<spdlog::logger> s_logger;

  static void init() noexcept;
  static spdlog::logger &get() noexcept;
  static void shutDown() noexcept;

  Logger() = delete;
  Logger(const Logger &other) = delete;
  Logger(Logger &&other) = delete;
  Logger &operator=(const Logger &other) = delete;
  Logger &operator=(Logger &&other) = delete;
  ~Logger() = delete;
};

#ifdef YAML_LOGGING_ENABLED
#define YAML_WARN(...) ::Yaml::Logger::get().warn(__VA_ARGS__);
#define YAML_CRITICAL(...) ::Yaml::Logger::get().critical(__VA_ARGS__);
#define YAML_INFO(...) ::Yaml::Logger::get().info(__VA_ARGS__);
#define YAML_DEBUG(...) ::Yaml::Logger::get().debug(__VA_ARGS__);
#define YAML_TRACE(...) ::Yaml::Logger::get().trace(__VA_ARGS__);
#define YAML_ERROR(...) ::Yaml::Logger::get().error(__VA_ARGS__);
#else
#define YAML_WARN(...)
#define YAML_CRITICAL(...)
#define YAML_INFO(...)
#define YAML_DEBUG(...)
#define YAML_TRACE(...)
#define YAML_ERROR(...)
#endif // YAML_LOGGING_ENABLED

} // namespace Yaml

#endif // __LOG_HPP