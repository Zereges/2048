#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_
#include <memory>
#include <SDL.h>
#include "..\Definitions\Definitions.hpp"

/*
 *  Singleton wrapper around SDL_Window and SDL_Renderer allowing creation and drawing on window.
 */
class Window
{
    public:
        static const Window& get_single();
        const SDL_Renderer* get_renderer() const { return m_renderer; }
        void clear() const;
        void add(const Rects& background) const;
        void add(const NumberedRects& blocks) const;
        void render_finish() const { SDL_RenderPresent(const_cast<SDL_Renderer*>(m_renderer)); }
        ~Window();

    private:
        const SDL_Window* m_window;
        const SDL_Renderer* m_renderer;
        static const Window* m_singleton;

        Window(std::size_t width, std::size_t height) : m_window(SDL_CreateWindow(Definitions::WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 0)), m_renderer(SDL_CreateRenderer(const_cast<SDL_Window*>(m_window), -1, SDL_RENDERER_ACCELERATED)) { }
};

#endif // _WINDOW_HPP_
