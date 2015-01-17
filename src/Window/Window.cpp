#include <SDL.h>
#include "Window.hpp"
#include "..\Game\Game.hpp"
const Window* Window::m_singleton = nullptr;

const Window& Window::get_single()
{
    if (m_singleton == nullptr)
        m_singleton = new Window(Definitions::WINDOW_WIDTH, Definitions::WINDOW_HEIGHT);
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

void Window::add(Game::Objects background) const
{
    for (auto iter = cbegin(background); iter != cend(background); ++iter)
        iter->draw();
}
