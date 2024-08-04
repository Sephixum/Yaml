#include "core/core.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <window.hpp>

namespace Yaml
{
    bool Window::m_is_sdl_initialized = false;

    void Window::init()
    {
        if (!m_is_sdl_initialized)
        {
            YAML_ASSERTM(
                SDL_Init(SDL_INIT_VIDEO),
                std::format("SDL failed to initialize: {}", SDL_GetError()))

        }
    }

    Window::Window(std::string_view window_title, uint8 window_x, uint8 window_y, uint16 window_width, uint16 window_height, uint32 window_flags)
    {
        this->m_sdl_window = SDL_CreateWindow(window_title.data(), window_x, window_y, window_width, window_height, window_flags);
        YAML_ASSERTM(
            this->m_sdl_window != nullptr,
            std::format("SDL failed to create window: {}", SDL_GetError())
        )

        SDL_Surface *window_surface = SDL_GetWindowSurface(this->m_sdl_window);

        YAML_ASSERTM(
            window_surface != nullptr,
            std::format("SDL failed to get window surface: {}", SDL_GetError())
        )

        SDL_FillRect(window_surface, nullptr, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));

        SDL_UpdateWindowSurface(this->m_sdl_window);
        SDL_Delay(5000);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(this->m_sdl_window);
    }

    Window::Builder &Window::Builder::set_title(std::string title)
    {
        this->m_window_title = title;
        return *this;
    }

    Window::Builder &Window::Builder::set_position(uint8 x, uint8 y) {
        this->m_window_x = x;
        this->m_window_y = y;
        return *this;
    }

    Window::Builder &Window::Builder::set_size(uint16 width, uint16 height) {
        this->m_window_width = width;
        this->m_window_height = height;
        return *this;
    }

    Window::Builder &Window::Builder::set_flags(uint32 flags) {
        this->m_window_flags = flags;
        return *this;
    }

    Window Window::Builder::build() {
        return Window(this->m_window_title, this->m_window_x, this->m_window_y, this->m_window_width, this->m_window_height, this->m_window_flags);
    }

} // namespace Yaml
