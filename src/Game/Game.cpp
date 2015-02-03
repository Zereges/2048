#include <SDL.h>
#include "Game.hpp"
#include "../Program/Program.hpp"
#include "../Definitions/Rect.hpp"
#include "../Definitions/NumberedRect.hpp"

Game::Game()
{
    m_background.emplace_back(Definitions::GAME_X, Definitions::GAME_Y, Definitions::BACKGROUND_COLOR, Definitions::GAME_WIDTH, Definitions::GAME_HEIGHT);
    for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
        for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
        {
            m_background.emplace_back(Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SIZE_X + Definitions::BLOCK_SPACE),
                Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SIZE_Y + Definitions::BLOCK_SPACE),
                Definitions::BLOCK_COLORS[0]);
        }

//    m_rects.emplace_back(get_block_coords(0, 0), Definitions::BLOCK_COLORS[1]);
}

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
        case SDLK_LEFT: play(LEFT); break;
        case SDLK_RIGHT: play(RIGHT); break;
        case SDLK_UP: play(UP); break;
        case SDLK_DOWN: play(DOWN); break;
            
    }
}

void Game::play(Directions direction)
{
    if (!can_play())
        return;

    for (auto iter = begin(m_rects); iter != end(m_rects); ++iter)
    {
        SDL_Point p;
        switch (direction)
        {
            case LEFT:
                p = get_block_coords(0, 0);
                p.y = iter->get_rect().y;
                break;
            case RIGHT:
                p = get_block_coords(3, 0);
                p.y = iter->get_rect().y;
                break;
            case UP:
                p = get_block_coords(0, 0);
                p.x = iter->get_rect().x;
                break;
            case DOWN:
                p = get_block_coords(0, 3);
                p.x = iter->get_rect().x;
                break;
        }
        m_animator.add_movement(*iter, p);
    }
}
