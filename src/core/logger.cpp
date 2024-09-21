#include "core/logger.hpp"

namespace Yaml {

std::shared_ptr<spdlog::logger> Logger::s_logger{nullptr};

void Logger::init() noexcept {
  s_logger = spdlog::stdout_color_mt("Console");
  s_logger->set_level(spdlog::level::trace);
}

spdlog::logger &Logger::get() noexcept {
  [[maybe_unused]] static auto _{std::invoke([]() {
    if (!s_logger) {
      init();
    }
    return 'c';
  })};

  return *s_logger;
}

void Logger::shutDown() noexcept { spdlog::shutdown(); }

} // namespace Yaml