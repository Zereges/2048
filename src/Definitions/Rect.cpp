#include <SDL.h>
#include "../Definitions/Rect.hpp"
#include "../Window/Window.hpp"

void Rect::draw() const
{
    SDL_Renderer* renderer = const_cast<SDL_Renderer*>(Window::get_single().get_renderer());
    SDL_SetRenderDrawColor(const_cast<SDL_Renderer*>(renderer), get_color().r, get_color().g, get_color().b, get_color().a);
    SDL_RenderFillRect(const_cast<SDL_Renderer*>(renderer), &get_rect());
}
