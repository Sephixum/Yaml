#include "core/core.hpp"
#include <window.hpp>

namespace Yaml
{
    bool Window::m_is_sdl_initialized = false;

    void Window::init()
    {
        if (!m_is_sdl_initialized)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            YAML_ASSERTM(
                SDL_Init(SDL_INIT_VIDEO) == 0,
                std::format("SDL failed to initialize: {}", SDL_GetError()));

            YAML_ASSERTM(
                SDL_GL_LoadLibrary(NULL) == 0,
                std::format("SDL failed to initialize OpenGL: {}", SDL_GetError()));

            this->m_is_sdl_initialized = true;
        }
    }

    Window::Window(std::string_view window_title, uint8 window_x, uint8 window_y, uint16 window_width, uint16 window_height, uint32 window_flags)
    {
        this->init();

        this->m_sdl_window = SDL_CreateWindow(window_title.data(), window_x, window_y, window_width, window_height, window_flags);
        YAML_ASSERTM(
            this->m_sdl_window != nullptr,
            std::format("SDL failed to create window: {}", SDL_GetError()))

        this->m_gl_context = SDL_GL_CreateContext(this->m_sdl_window);

        YAML_ASSERTM(
            this->m_gl_context != nullptr,
            "SDL failed to create OpenGL context")

        this->makeContextCurrent();

        YAML_ASSERTM(
            gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)),
            "Failed to initialize GLAD")

        SDL_Event event;
        int w, h;
        this->set_vsync(Window::VSyncTypes::NORMAL);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        SDL_GetWindowSize(this->m_sdl_window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
        bool quit = false;

        while (!quit)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(this->m_sdl_window);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_q)
                    {
                        quit = true;
                    }
                }
            }
        }
    }

    void Window::makeContextCurrent()
    {
        SDL_GL_MakeCurrent(this->m_sdl_window, this->m_gl_context);
    }

    void Window::set_vsync(VSyncTypes type)
    {
        SDL_GL_SetSwapInterval(static_cast<int>(type));
    }

    Window::VSyncTypes Window::get_vsync_type() const
    {
        int interval_type = SDL_GL_GetSwapInterval();
    }

    Window::~Window()
    {
        SDL_DestroyWindow(this->m_sdl_window);
    }

    Window::Builder &Window::Builder::setTitle(std::string title)
    {
        this->m_window_title = title;
        return *this;
    }

    Window::Builder &Window::Builder::setPosition(uint8 x, uint8 y)
    {
        this->m_window_x = x;
        this->m_window_y = y;
        return *this;
    }

    Window::Builder &Window::Builder::setSize(uint16 width, uint16 height)
    {
        this->m_window_width = width;
        this->m_window_height = height;
        return *this;
    }

    Window::Builder &Window::Builder::setFlags(uint32 flags)
    {
        this->m_window_flags = flags;
        return *this;
    }

    Window Window::Builder::build()
    {
        return Window(this->m_window_title, this->m_window_x, this->m_window_y, this->m_window_width, this->m_window_height, this->m_window_flags);
    }

} // namespace Yaml
