#pragma once

#include <GLFW/glfw3.h>

#include "application/window_interface.hpp"

namespace Yaml {

class OpenGLWindow : public IWindow {
protected:
  GLFWwindow *m_window;

  struct {
    std::string title;
    uint32 width{}, height{};
    bool vsync{};
    event_callback_func event_callback;
  } m_data{};

private:
  virtual void _init(const WindowProps &props);
  virtual void _shutDown();

public:
  OpenGLWindow(const WindowProps &props);
  OpenGLWindow(const OpenGLWindow &other) = delete;
  OpenGLWindow &operator=(const OpenGLWindow &rhs) = delete;
  OpenGLWindow(OpenGLWindow &&other) = default;
  OpenGLWindow &operator=(OpenGLWindow &&rhs) = default;
  virtual ~OpenGLWindow();

  virtual void onUpdate() override;
  uint32 getWidth() const noexcept override;
  uint32 getHeight() const noexcept override;

  virtual void setEventCallback(const event_callback_func &call_back) override;
  virtual void setVSync(bool enabled) noexcept override;
  virtual bool isVSync() const noexcept override;
};

} // namespace Yaml
