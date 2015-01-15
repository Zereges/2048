#include <SDL.h>
#include "Game.hpp"
#include "../Program/Program.hpp"

void Game::event_handler(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            Program::stop(true);
            break;
        case SDL_KEYDOWN:
            key_handler(event.key);
            break;
    }
}

void Game::key_handler(const SDL_KeyboardEvent& keyevent)
{
    switch (keyevent.keysym.sym)
    {
        case SDLK_q:
            if (keyevent.keysym.mod & (KMOD_RCTRL | KMOD_LCTRL))
            {
                Program::stop(false);
            }
            break;
    }
}
