#ifndef _STATS_WINDOW_HPP_
#define _STATS_WINDOW_HPP_
#include <memory>
#include <SDL.h>
#include "Window.hpp"
#include "../Definitions/Definitions.hpp"
#include "../Stats/Stats.hpp"

/*
 *  Wrapper around SDL_Window and SDL_Renderer allowing creation and drawing rects on window.
 */
class StatsWindow : public Window
{
    public:
        StatsWindow(std::size_t width, std::size_t height, std::string name, const Stats& stats_current, Stats&& tmp_stats);
        ~StatsWindow();

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
