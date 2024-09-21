#include "opengl_window.hpp"

namespace Yaml {

static auto s_GLFW_initialized{false};

IWindow *IWindow::create(const WindowProps &props) {
  return new OpenGLWindow(props);
}

void OpenGLWindow::_init(const WindowProps &props) {
  m_data.title = props.title;
  m_data.width = props.width;
  m_data.height = props.height;

  YAML_INFO("Creating window \n"
            "-- Title: {}\n"
            "-- Width: {}\n"
            "-- Height: {}",
            props.title, props.width, props.height);

  if (!s_GLFW_initialized) {
    auto success{glfwInit()};
    YAML_ASSERTM(success, "Could not initialize GLFW!");
    s_GLFW_initialized = true;
  }

  m_window = glfwCreateWindow(static_cast<int>(m_data.width),  //
                              static_cast<int>(m_data.height), //
                              m_data.title.c_str(),            //
                              nullptr, nullptr                 //
  );

  glfwMakeContextCurrent(m_window);
  glfwSetWindowUserPointer(m_window, &m_data);
  setVSync(true);
}

void OpenGLWindow::_shutDown() { glfwDestroyWindow(m_window); }

OpenGLWindow::OpenGLWindow(const WindowProps &props) { _init(props); }

OpenGLWindow::~OpenGLWindow() { _shutDown(); }

uint32 OpenGLWindow::getWidth() const noexcept { return m_data.width; }

uint32 OpenGLWindow::getHeight() const noexcept { return m_data.height; }

void OpenGLWindow::onUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_window);
}

void OpenGLWindow::setEventCallback(const event_callback_func &call_back) {
  (void)call_back;
  YAML_ASSERT(false);
}

bool OpenGLWindow::isVSync() const noexcept { return m_data.vsync; }

void OpenGLWindow::setVSync(bool enabled) noexcept {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }

  m_data.vsync = enabled;
}

} // namespace Yaml
