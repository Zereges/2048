#include <SDL.h>
#include <iostream>
#include "Program.hpp"
#include "../Window/Window.hpp"
#include "../Game/Game.hpp"
bool Program::m_is_running = false;
int Program::m_ret_value = EXIT_SUCCESS;

int Program::start()
{
    const Window& window = Window::get_single();
    Game game;
    m_is_running = true;
    SDL_Event event;
    while (is_running())
    {
        while (SDL_PollEvent(&event))
        {
            game.event_handler(event);
        }
        window.clear();
        window.add(game.get_background());
        window.render_finish();
    }
    return m_ret_value;
}

void Program::stop(bool force)
{
    m_is_running = false;
}
