#include <SDL.h>
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
        }
    }
    close();
}
