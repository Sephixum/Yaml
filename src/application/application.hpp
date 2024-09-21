#pragma once

#include "core/core.hpp"
#include "window_interface.hpp"

namespace Yaml {

class Application {
private:
  inline static Application *s_instance{nullptr};
  std::unique_ptr<IWindow> m_window{nullptr};
  bool m_running{true};

  Application();

public:
  virtual ~Application();
  Application(const Application &other) = delete;
  Application(Application &&other) = delete;
  Application &operator=(const Application &rhs) = delete;
  Application &operator=(Application &&rhs) = delete;

  static Application &getInstance() noexcept;
  void run();
};

} // namespace Yaml