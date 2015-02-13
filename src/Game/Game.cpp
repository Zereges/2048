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
    m_state.resize(Definitions::BLOCK_COUNT_X, std::vector<const Rect*>(Definitions::BLOCK_COUNT_Y, nullptr));
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
        case SDLK_r: restart(); break; // TBD
        case SDLK_b: random_block(chance(Definitions::BLOCK_4_SPAWN_CHANCE) ? BLOCK_4 : BLOCK_2); break; // TBD
    }
}

void Game::start()
{
    for (int i = 0; i < Definitions::DEFAULT_START_BLOCKS; ++i)
        random_block(chance(Definitions::BLOCK_4_SPAWN_CHANCE) ? BLOCK_4 : BLOCK_2);
}

void Game::play(Directions direction)
{
    if (!can_play())
        return;

    for (auto iter = begin(m_rects); iter != end(m_rects); ++iter)
    {
        SDL_Point p;
        switch (direction) // ToDo: here
        {
            case LEFT:
                p = get_block_coords(0, 0);
                p.y = iter->get_rect().y;
                break;
            case RIGHT:
                p = get_block_coords(Definitions::BLOCK_COUNT_X - 1, 0);
                p.y = iter->get_rect().y;
                break;
            case UP:
                p = get_block_coords(0, 0);
                p.x = iter->get_rect().x;
                break;
            case DOWN:
                p = get_block_coords(0, Definitions::BLOCK_COUNT_Y - 1);
                p.x = iter->get_rect().x;
                break;
        }
        m_animator.add_movement(*iter, p);
    }
}

bool Game::random_block(Blocks block)
{
    if (!can_play())
        return false;
    std::vector<int> poss;
    for (size_t i = 0; i < Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y; ++i)
        if (m_state[i / Definitions::BLOCK_COUNT_X][i % Definitions::BLOCK_COUNT_Y] == 0)
            poss.push_back(i);
    if (poss.size() == 0)
        return false;
    size_t pos = poss[rand() % poss.size()];
    m_rects.emplace_back(get_block_coords(pos / Definitions::BLOCK_COUNT_X, pos % Definitions::BLOCK_COUNT_Y), block);
    m_state[pos / Definitions::BLOCK_COUNT_X][pos % Definitions::BLOCK_COUNT_Y] = &(m_rects[m_rects.size() - 1]);
    return true;
}

void Game::restart()
{
    m_state = State(Definitions::BLOCK_COUNT_X, std::vector<const Rect*>(Definitions::BLOCK_COUNT_Y, nullptr));
    m_rects.clear();
    start();
}
