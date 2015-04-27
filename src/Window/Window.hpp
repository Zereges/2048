#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_
#include <memory>
#include <string>
#include <SDL.h>
#include "..\Definitions\Definitions.hpp"

/*
 *  Wrapper around SDL_Window and SDL_Renderer allowing creation and drawing rects on window.
 */
class Window
{
    public:
        Window(std::size_t width, std::size_t height, std::string name) : m_window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 0)), m_renderer(SDL_CreateRenderer(const_cast<SDL_Window*>(m_window), -1, SDL_RENDERER_ACCELERATED)) { }

        const SDL_Renderer* get_renderer() const { return m_renderer; }
        void clear() const;
        void hide() const { SDL_HideWindow(m_window); }
        void show() const { SDL_ShowWindow(m_window); }
        void warning(const std::string& text) const { SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_WARNING, "Warning", text.c_str(), m_window); }
        void render_finish() const { SDL_RenderPresent(const_cast<SDL_Renderer*>(m_renderer)); }
        void close() { SDL_DestroyWindow(m_window); }
        ~Window();

    protected:
        SDL_Window* m_window;
        const SDL_Renderer* m_renderer;
};

#endif // _WINDOW_HPP_
