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
    m_rects.resize(Definitions::BLOCK_COUNT_X, std::vector<std::shared_ptr<NumberedRect>>(Definitions::BLOCK_COUNT_Y, nullptr));
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

    // case LEFT:
    for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
    {
        for (std::size_t x = 1; x < Definitions::BLOCK_COUNT_X; ++x)
        {
            if (m_rects[x][y] == nullptr)
                continue;
            std::size_t i = x;
            while (i != 0 && m_rects[i - 1][y] != nullptr) --i;
            move_to(*m_rects[x][y], i, y);
        }
    }

    on_turn_end();
}

void Game::on_turn_end()
{

}

void Game::move_to(NumberedRect& rect, std::size_t x, std::size_t y)
{
    m_animator.add_movement(rect, get_block_coords(x, y));
    *m_rects[x][y] = std::move(rect);
}

bool Game::random_block(Blocks block)
{
    if (!can_play())
        return false;
    std::vector<int> poss;
    for (size_t i = 0; i < Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y; ++i)
        if (m_rects[i / Definitions::BLOCK_COUNT_X][i % Definitions::BLOCK_COUNT_Y] == nullptr)
            poss.push_back(i);
    if (poss.size() == 0)
        return false;
    size_t pos = poss[rand() % poss.size()];
    m_rects[pos / Definitions::BLOCK_COUNT_X][pos % Definitions::BLOCK_COUNT_Y] =
        std::make_shared<NumberedRect>(get_block_coords(pos / Definitions::BLOCK_COUNT_X, pos % Definitions::BLOCK_COUNT_Y), block);
    return true;
}

void Game::restart()
{
    m_rects = NumberedRects(Definitions::BLOCK_COUNT_X, std::vector<std::shared_ptr<NumberedRect>>(Definitions::BLOCK_COUNT_Y, nullptr));
    start();
}
