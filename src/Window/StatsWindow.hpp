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
        StatsWindow(std::size_t width, std::size_t height, std::string name, const Stats& stats) : Window(width, height, name), m_stats(stats) { }
        // Shows statistics and waits for user to close the window.
        void wait_for_close();

    private:
        const Stats& m_stats;
};

#endif // _STATS_WINDOW_HPP_
