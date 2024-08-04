#ifndef __WINDOW_HPP
#define __WINDOW_HPP

#include "core/defines.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <core/pch.hpp>

namespace Yaml {

class Window {
  private:
    SDL_Window *m_sdl_window = nullptr;
    SDL_GLContext m_gl_context = nullptr;
    bool m_is_vsync_enabled = false;
    static bool m_is_sdl_initialized;
    void make_context_current();
    void init();
    Window(std::string_view window_title, uint8 window_x, uint8 window_y,
           uint16 window_width, uint16 window_height, uint32 window_flags);

  public:
    ~Window();

    enum class VSyncTypes {
      OFF = 0,
      NORMAL = 1,
      ADAPTIVE = -1
    };

    void set_vsync(VSyncTypes type);
    VSyncTypes get_vsync_type() const;

    class Builder {
      private:
        std::string m_window_title = "YAML Window";
        uint32 m_window_x = SDL_WINDOWPOS_CENTERED;
        uint32 m_window_y = SDL_WINDOWPOS_CENTERED;
        uint16 m_window_width = 800;
        uint16 m_window_height = 600;
        uint32 m_window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

      public:
        Builder() = default;
        Builder &set_title(std::string title);
        Builder &set_position(uint8 x, uint8 y);
        Builder &set_size(uint16 width, uint16 height);
        Builder &set_flags(uint32 flags);
        Window build();
    };
};

} // namespace Yaml

#endif // __WINDOW_HPP
