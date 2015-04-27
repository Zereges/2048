#include <SDL.h>
#include <iostream>
#include "StatsWindow.hpp"

void StatsWindow::wait_for_close()
{
    bool show = true;    
    SDL_Event event;
    while (show)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                show = false;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (switch_button_clicked(event.button))
                    switch_stats();
                break;
            }
        }
    }
    close();
}

void StatsWindow::switch_stats()
{
    m_showing_current = !m_showing_current;
    int width, height; /* = */ SDL_GetWindowSize(m_window, &width, &height);
    TTF_Font* font = TTF_OpenFont(Definitions::DEFAULT_FONT_NAME.c_str(), (int) 1.2 * Definitions::STATS_FONT_SIZE);
    SDL_Surface* textSurface;

    if (m_showing_current)
    {
        textSurface = TTF_RenderText_Blended(font, "Switch to Global Stats", Definitions::WHITE_COLOR);
        texture_button = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
        rect_button = { (width - textSurface->w) / 2, height - Definitions::STATS_BUTTON_HEIGHT, textSurface->w, Definitions::STATS_BUTTON_HEIGHT };

        SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect_current);
        SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect_button);
        SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture_current, NULL, &rect_current);
        SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture_button, NULL, &rect_button);
        SDL_RenderPresent(const_cast<SDL_Renderer*>(get_renderer()));
    }
    else
    {
        textSurface = TTF_RenderText_Blended(font, "Switch to Local Stats", Definitions::WHITE_COLOR);
        texture_button = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
        rect_button = { (width - textSurface->w) / 2, height - Definitions::STATS_BUTTON_HEIGHT, textSurface->w, Definitions::STATS_BUTTON_HEIGHT };

        SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect_global);
        SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect_button);
        SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture_global, NULL, &rect_global);
        SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture_button, NULL, &rect_button);
        SDL_RenderPresent(const_cast<SDL_Renderer*>(get_renderer()));
    }
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}
