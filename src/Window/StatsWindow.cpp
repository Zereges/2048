#include <SDL.h>
#include "StatsWindow.hpp"

void StatsWindow::wait_for_close()
{
    bool show = true;    
    SDL_Event event;

    TTF_Font* font = TTF_OpenFont(Definitions::DEFAULT_BLOCK_FONT_NAME.c_str(), Definitions::STATS_FONT_SIZE);
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, m_stats.to_string().c_str(), Definitions::DEFAULT_BLOCK_FONT_COLOR, 500);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
    SDL_Rect rect = { 0, 0, textSurface->w, textSurface->h };
    SDL_FreeSurface(textSurface);
    SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect);
    SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture, NULL, &rect);
    SDL_RenderPresent(const_cast<SDL_Renderer*>(get_renderer()));

    while (show)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                show = false;
                break;
            }
        }
    }
    close();
}
