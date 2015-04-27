#ifndef _STATS_WINDOW_HPP_
#define _STATS_WINDOW_HPP_
#include <memory>
#include <SDL.h>
#include "Window.hpp"
#include "..\Definitions\Definitions.hpp"
#include "..\Stats\Stats.hpp"

/*
 *  Wrapper around SDL_Window and SDL_Renderer allowing creation and drawing rects on window.
 */
class StatsWindow : public Window
{
    public:
        StatsWindow(std::size_t width, std::size_t height, std::string name, const Stats& stats_current, Stats&& tmp_stats) :
            Window(width, height, name), m_stats_current(stats_current), m_stats_global(tmp_stats), m_showing_current(true)
        {
            TTF_Font* font = TTF_OpenFont(Definitions::DEFAULT_FONT_NAME.c_str(), Definitions::STATS_FONT_SIZE);
            
            SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, m_stats_current.to_string().c_str(), Definitions::WHITE_COLOR, width);
            texture_current = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            rect_current = { 0, 0, textSurface->w, textSurface->h };
            SDL_FreeSurface(textSurface);

            textSurface = TTF_RenderText_Blended_Wrapped(font, tmp_stats.to_string().c_str(), Definitions::WHITE_COLOR, width);
            texture_global = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            rect_global = { 0, 0, textSurface->w, textSurface->h };
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);

            font = TTF_OpenFont(Definitions::DEFAULT_FONT_NAME.c_str(), (int) 1.2 * Definitions::STATS_FONT_SIZE);
            textSurface = TTF_RenderText_Blended(font, "Switch to Global Stats", Definitions::WHITE_COLOR);
            texture_button = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            rect_button = { (width - textSurface->w) / 2, height - Definitions::STATS_BUTTON_HEIGHT, textSurface->w, Definitions::STATS_BUTTON_HEIGHT };
            SDL_FreeSurface(textSurface);

            TTF_CloseFont(font);

            SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect_current);
            SDL_RenderFillRect(const_cast<SDL_Renderer*>(get_renderer()), &rect_button);
            SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture_current, NULL, &rect_current);
            SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), texture_button, NULL, &rect_button);
            SDL_RenderPresent(const_cast<SDL_Renderer*>(get_renderer()));
        }
        ~StatsWindow() { SDL_DestroyTexture(texture_current); }

        // Shows statistics and waits for user to close the window.
        void wait_for_close();

        // Tells whether mouse was clicked in rect_button.
        // Params: event - SDL_MouseButtonEvent with information about mouse click.
        // Returns: true if switch button was clicked, false otherwise.
        bool switch_button_clicked(const SDL_MouseButtonEvent& event)
        {
            return rect_button.x <= event.x && event.x <= rect_button.x + rect_button.w &&
                   rect_button.y <= event.y && event.y <= rect_button.y + rect_button.h;
        }

        // Changes text regarding Current or Global statistics.
        void switch_stats();

    private:
        const Stats& m_stats_current;
        const Stats& m_stats_global;
        bool m_showing_current;
        SDL_Texture* texture_current;
        SDL_Texture* texture_global;
        SDL_Texture* texture_button;
        SDL_Rect rect_current;
        SDL_Rect rect_global;
        SDL_Rect rect_button;
};

#endif // _STATS_WINDOW_HPP_
