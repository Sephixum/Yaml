#ifndef __WINDOW_HPP
#define __WINDOW_HPP

#include <core/core.hpp>

namespace Yaml {

struct WindowProps {
  std::string title{"Yaml window"};
  uint32 width{1280};
  uint32 height{720};

  WindowProps() = default;
  WindowProps(const std::string &title, uint32 width, uint32 height) noexcept
      : title(title), width{width}, height{height} {}
};

class Event;

class IWindow {
public:
  using event_callback_func = std::function<void(Event &)>;

  static IWindow *create(const WindowProps &props = WindowProps{});

  IWindow() = default;
  IWindow(const IWindow &other) = delete;
  IWindow &operator=(const IWindow &rhs) = delete;
  IWindow(IWindow &&other) = default;
  IWindow &operator=(IWindow &&rhs) = default;
  virtual ~IWindow() = default;

  virtual void onUpdate() = 0;
  virtual uint32 getWidth() const noexcept = 0;
  virtual uint32 getHeight() const noexcept = 0;

  virtual void setEventCallback(const event_callback_func &call_back) = 0;
  virtual void setVSync(bool enabled) noexcept = 0;
  virtual bool isVSync() const noexcept = 0;
};

} // namespace Yaml

#endif // __WINDOW_HPP
