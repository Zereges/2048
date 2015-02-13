#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
#include <vector>
#include <exception>
#include "..\Definitions\Definitions.hpp"
#include "..\Definitions\Rect.hpp"
#include "..\Definitions\NumberedRect.hpp"
#include "..\Animation\Animator.hpp"
/*  
 *  Game class handling user events.
 */
class Game
{
    public:
        Game();
        void event_handler(const SDL_Event& event);
        void key_handler(const SDL_KeyboardEvent& key);
        const Rects& get_background() const { return m_background; }
        const NumberedRects& get_rects() const { return m_rects; }
        static SDL_Point get_block_coords(unsigned int x, unsigned int y)
        {
            if (x < 0 || x >= Definitions::BLOCK_COUNT_X || y < 0 || y >= Definitions::BLOCK_COUNT_Y)
                throw std::runtime_error("Invalid coords for Game::get_block_coords(unsigned, unsigned)");
            return { Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X),
                     Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)
                   };
        }
        static std::pair<int, int> get_coords_block(const Rect& rect)
        {
            return {(rect.get_rect().x - Definitions::GAME_X - Definitions::BLOCK_SPACE) / (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X), 
                    (rect.get_rect().y - Definitions::GAME_Y - Definitions::BLOCK_SPACE) / (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)};
        }
        const Rect& get_block_on_coords(unsigned int x, unsigned int y) const
        {
            for (auto iter = m_rects.cbegin(); iter != m_rects.cend(); ++iter)
            {
                if (get_coords_block(*iter).first == x && get_coords_block(*iter).second == y)
                    return *iter;
            }
            throw std::runtime_error("Block does not exists at given [x, y]");

        }
        // Starts new game.
        void start();
        void animate() { m_animator.animate(); }
        bool can_play() { return m_animator.can_play(); }
        void play(Directions direction);

        // Inserts random block on board and updates state.
        // Param: block - Block to insert
        // Returns: true on success, false on failure (full board, can't play)
        bool random_block(Blocks block);

        // Removes all progress in current game and starts new one.
        void restart();

    private:
        Rects m_background;
        NumberedRects m_rects;
        State m_state;
        Animator m_animator;
};

#endif // _GAME_HPP_
