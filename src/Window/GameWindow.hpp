#ifndef _GAME_WINDOW_HPP_
#define _GAME_WINDOW_HPP_
#include <memory>
#include <SDL.h>
#include "Window.hpp"
#include "..\Definitions\Definitions.hpp"

/*
 *  Wrapper around SDL_Window and SDL_Renderer allowing creation and drawing rects on window.
 */
class GameWindow : public Window
{
    public:
        GameWindow(std::size_t width, std::size_t height, std::string name) : Window(width, height, name)
        {
            game_window_font = TTF_OpenFont(Definitions::DEFAULT_FONT_NAME.c_str(), 20);

            SDL_Surface* textSurface = TTF_RenderText_Blended(game_window_font, "GAME OVER! Press R for restart.", Definitions::BLACK_COLOR);
            game_over_texture = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            game_over_rect = { (Definitions::GAME_WIDTH - textSurface->w) / 2, (Definitions::GAME_HEIGHT - textSurface->h) / 2, textSurface->w, textSurface->h };
            SDL_FreeSurface(textSurface);

            textSurface = TTF_RenderText_Blended(game_window_font, "Score: 0", Definitions::WHITE_COLOR);
            game_score_texture = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            game_score_rect = { 4, 4, textSurface->w, Definitions::GAME_Y - 8 };
            SDL_FreeSurface(textSurface);

            textSurface = TTF_RenderText_Blended(game_window_font, "Show Stats", Definitions::WHITE_COLOR);
            stats_texture = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            stats_rect = { Definitions::GAME_WIDTH - textSurface->w - 4, 4, textSurface->w, Definitions::GAME_Y - 8 };
            SDL_FreeSurface(textSurface);
        }
        ~GameWindow()
        {
            TTF_CloseFont(game_window_font);
            SDL_DestroyTexture(game_over_texture);
            SDL_DestroyTexture(stats_texture);
            if (game_score_texture != nullptr)
                SDL_DestroyTexture(game_score_texture);
        }
        // Adds Rects for showing as background.
        // Params: background - Rects representing the background.
        void add(const Rects& background);

        // Adds NumberedRects for showing as game state.
        // Params: rects - NumberedRects representing game state.
        void add(const NumberedRects& rects);

        // Displayes game over message.
        // Params: yes - display toggle.
        void display_game_over(bool yes) { if (yes) SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), game_over_texture, NULL, &game_over_rect); }

        // Displays game score.
        void display_score() { SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), game_score_texture, NULL, &game_score_rect); }

        // Displays statistics button.
        void display_stats_button() { SDL_RenderCopy(const_cast<SDL_Renderer*>(get_renderer()), stats_texture, NULL, &stats_rect); }

        // Updates game score from string.
        // Params: score - string to show.
        void update_score(std::string score)
        {
            SDL_Surface* textSurface = TTF_RenderText_Blended(game_window_font, ("Score: " + score).c_str(), Definitions::WHITE_COLOR);
            game_score_texture = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(get_renderer()), textSurface);
            game_score_rect.w = textSurface->w;
            SDL_FreeSurface(textSurface);
        }
        
        // Tells whether mouse was clicked in stats_rect.
        // Params: event - SDL_MouseButtonEvent with information about mouse click.
        // Returns: true if button was clicked, false otherwise.
        bool stats_button_clicked(const SDL_MouseButtonEvent& event)
        {
            return stats_rect.x <= event.x && event.x <= stats_rect.x + stats_rect.w &&
                   stats_rect.y <= event.y && event.y <= stats_rect.y + stats_rect.h;
        }

    private:
        TTF_Font* game_window_font;         // Font used for whowing score.
        SDL_Texture* game_over_texture;     // Texture used for text display of player's game over.
        SDL_Rect game_over_rect;            // Position of game over text.
        SDL_Texture* game_score_texture;    // Texture used for displaying score.
        SDL_Rect game_score_rect;           // Position of game score.
        SDL_Texture* stats_texture;         // Texture used for displaying stats button.
        SDL_Rect stats_rect;                // Position of stats button.
};

#endif // _GAME_WINDOW_HPP_
