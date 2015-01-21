#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
#include <vector>
#include <exception>
#include "../Definitions/Rect.hpp"
/*  
 *  Game class handling user events.
 */
class Game
{
    public:
        typedef std::vector<Rect> Objects;

        void event_handler(const SDL_Event& event);
        void key_handler(const SDL_KeyboardEvent& key);
        const Objects& get_background() const { return m_background; }
        SDL_Point get_block_coords(unsigned int x, unsigned int y) const
        {
            if (x < 0 || x >= Definitions::BLOCK_COUNT_X || y < 0 || y >= Definitions::BLOCK_COUNT_Y)
                throw std::runtime_error("Invalid coords for Game::get_block_coords(unsigned, unsigned)");
            return { Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X),
                     Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)
                   };
        }
        Game();
    
    private:
        Objects m_background;
};

#endif // _GAME_HPP_
