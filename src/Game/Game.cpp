#include <SDL.h>
#include "Game.hpp"
#include <assert.h>
#include "../Program/Program.hpp"
#include "../Definitions/Rect.hpp"
#include "../Definitions/NumberedRect.hpp"
#include "../Animation/Move.hpp"
#include "../Animation/Spawn.hpp"
#include "../Animation/Merge.hpp"
#define assert_coords(x, y) assert((x) >= 0 && (x) < Definitions::BLOCK_COUNT_X && (y) >= 0 && (y) < Definitions::BLOCK_COUNT_Y)

Game::Game() : m_canplay(false)
{
    m_background.emplace_back(0, 0, Definitions::BACKGROUND_COLOR, Definitions::GAME_WIDTH, Definitions::GAME_HEIGHT);
    for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
        for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
        {
            m_background.emplace_back(Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SIZE_X + Definitions::BLOCK_SPACE),
                Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SIZE_Y + Definitions::BLOCK_SPACE),
                Definitions::get_block_color(0));
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
        case SDLK_b: random_block(); break; // TBD
        case SDLK_s: stop(); break; // TBD
        case SDLK_e: // TBD
            m_rects = NumberedRects(Definitions::BLOCK_COUNT_X, std::vector<std::shared_ptr<NumberedRect>>(Definitions::BLOCK_COUNT_Y, nullptr));
            for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
                for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
                    m_rects[x][y] = std::make_shared<NumberedRect>(get_block_coords(x, y), ((x + y) % 2) ? 2 : 1);
            break;
    }
}

void Game::start()
{
    for (int i = 0; i < Definitions::DEFAULT_START_BLOCKS; ++i)
        random_block();
    m_canplay = true;
}

void Game::play(Directions direction)
{
    if (!can_play())
        return;

    m_stats.play(direction);

    switch (direction)
    {
        case LEFT:
            for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
            {
                for (std::size_t x = 1; x < Definitions::BLOCK_COUNT_X; ++x)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = x;
                    while (i > 0 && m_rects[--i][y] == nullptr); // find closest block
                    if (can_merge(m_rects[x][y], m_rects[i][y]))
                        merge_to(x, y, i, y);
                    else if (m_rects[i][y] == nullptr || m_rects[++i][y] == nullptr)
                        move_to(x, y, i, y);
                }
            }
            break;
        case RIGHT:
            for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
            {
                for (int x = Definitions::BLOCK_COUNT_X - 2; x >= 0; --x)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = x;
                    while (i < Definitions::BLOCK_COUNT_X - 1 && m_rects[++i][y] == nullptr);
                    if (can_merge(m_rects[x][y], m_rects[i][y]))
                        merge_to(x, y, i, y);
                    else if (m_rects[i][y] == nullptr || m_rects[--i][y] == nullptr)
                        move_to(x, y, i, y);
                }
            }
            break;
        case UP:
            for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
            {
                for (std::size_t y = 1; y < Definitions::BLOCK_COUNT_Y; ++y)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = y;
                    while (i > 0 && m_rects[x][--i] == nullptr); // find closest block
                    if (can_merge(m_rects[x][y], m_rects[x][i]))
                        merge_to(x, y, x, i);
                    else if (m_rects[x][i] == nullptr || m_rects[x][++i] == nullptr)
                        move_to(x, y, x, i);
                }
            }
            break;
        case DOWN:
            for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
            {
                for (int y = Definitions::BLOCK_COUNT_Y - 2; y >= 0; --y)
                {
                    if (m_rects[x][y] == nullptr)
                        continue;
                    std::size_t i = y;
                    while (i < Definitions::BLOCK_COUNT_Y - 1 && m_rects[x][++i] == nullptr);
                    if (can_merge(m_rects[x][y], m_rects[x][i]))
                        merge_to(x, y, x, i);
                    else if (m_rects[x][i] == nullptr || m_rects[x][--i] == nullptr)
                        move_to(x, y, x, i);
                }
            }
            break;
    }

    on_turn_end();
}

void Game::on_turn_end()
{
    random_block();
    if (is_game_over())
        stop();
}

void Game::move_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y)
{
    assert_coords(from_x, from_y);
    assert_coords(to_x, to_y);
    assert(m_rects[from_x][from_y] != nullptr && m_rects[to_x][to_y] == nullptr);
    m_animator.add<Move>(*m_rects[from_x][from_y], get_block_coords(to_x, to_y));
    m_rects[to_x][to_y] = m_rects[from_x][from_y];
    m_rects[from_x][from_y] = nullptr;

    m_stats.move();
}

void Game::merge_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y)
{
    assert_coords(from_x, from_y);
    assert_coords(to_x, to_y);
    assert(m_rects[from_x][from_y] != nullptr && m_rects[to_x][to_y] != nullptr);
    m_animator.add<Merge>(*m_rects[to_x][to_y]);
    m_rects[to_x][to_y]->next_number();
    m_rects[from_x][from_y] = nullptr;

    m_stats.merge();
}

bool Game::spawn_block(Blocks block, std::size_t x, std::size_t y)
{
    assert_coords(x, y);
    if (m_rects[x][y])
        return false;
    m_rects[x][y] = std::make_shared<NumberedRect>(get_block_coords(x, y), block, 0, 0);
    m_animator.add<Spawn>(*m_rects[x][y], get_block_coords(x, y));

    return true;
}

bool Game::random_block(Blocks block)
{
    std::vector<int> poss;
    for (std::size_t i = 0; i < Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y; ++i)
        if (m_rects[i / Definitions::BLOCK_COUNT_X][i % Definitions::BLOCK_COUNT_Y] == nullptr)
            poss.push_back(i);
    if (poss.size() == 0)
        return false;

    size_t pos = poss[rand() % poss.size()];
    return spawn_block(block, pos / Definitions::BLOCK_COUNT_X, pos % Definitions::BLOCK_COUNT_Y);
}

void Game::restart()
{
    m_canplay = false;
    m_stats.restart();
    m_rects = NumberedRects(Definitions::BLOCK_COUNT_X, std::vector<std::shared_ptr<NumberedRect>>(Definitions::BLOCK_COUNT_Y, nullptr));
    start();
}

bool Game::is_game_over()
{
    for (auto i = m_rects.begin(); i != m_rects.end(); ++i)
        for (auto j = i->begin(); j != i->end(); ++j)
            if ((*j) == nullptr)
                return false;
    // Board is full, looking for merge.
    for (std::size_t x = 0; x < Definitions::BLOCK_COUNT_X - 1; ++x)
        for (std::size_t y = 0; y < Definitions::BLOCK_COUNT_Y - 1; ++y)
        {
            if (can_merge(m_rects[x][y], m_rects[x][y + 1]))
                return false;
            if (can_merge(m_rects[x][y], m_rects[x + 1][y]))
                return false;
        }

    return true;
}
