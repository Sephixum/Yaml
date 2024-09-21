#include "application.hpp"

namespace Yaml {

Application::Application() {
  m_window = std::unique_ptr<IWindow>(IWindow::create());
}

Application::~Application() {}

Application &Application::getInstance() noexcept {
  [[maybe_unused]] static auto _{std::invoke([]() {
    if (!s_instance) {
      s_instance = new Application();
    }
    return 'c';
  })};

  return *s_instance;
}

void Application::run() {
  while (m_running) {
    m_window->onUpdate();
  }
}

} // namespace Yaml
