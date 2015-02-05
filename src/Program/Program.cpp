#include <SDL.h>
#include <iostream>
#include "Program.hpp"
#include "../Window/Window.hpp"
#include "../Game/Game.hpp"
#include "../Animation/Animator.hpp"
bool Program::m_is_running = false;
int Program::m_ret_value = EXIT_SUCCESS;

int Program::start(const std::vector<std::string>& args)
{
    const Window& window = Window::get_single();
    Game game;
    game.start();
    m_is_running = true;
    SDL_Event event;
    while (is_running())
    {
        while (SDL_PollEvent(&event))
        {
            game.event_handler(event);
        }
        game.animate();
        window.clear();
        window.add(game.get_background());
        window.add(game.get_rects());
        window.render_finish();
    }
    return m_ret_value;
}

void Program::stop(bool force)
{
    m_is_running = false;
}
