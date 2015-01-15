#include "Window.hpp"
#include <SDL.h>
const Window* Window::m_singleton = nullptr;

const Window& Window::get_single()
{
    if (m_singleton == nullptr)
        m_singleton = new Window(Definitions::WIDTH, Definitions::HEIGHT);
    return *m_singleton;
}

Window::~Window()
{
    SDL_DestroyRenderer(const_cast<SDL_Renderer*>(m_renderer));
    SDL_DestroyWindow(const_cast<SDL_Window*>(m_window));
    if (m_singleton != nullptr)
        delete m_singleton;
}

void Window::clear() const
{
    SDL_SetRenderDrawColor(const_cast<SDL_Renderer*>(m_renderer), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(const_cast<SDL_Renderer*>(m_renderer));
}
