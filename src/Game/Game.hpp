#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
#include <vector>
#include "../Definitions/Rect.hpp"
/*  
 *  Game class handling user events.
 */
class Game
{
    public:
        void event_handler(const SDL_Event& event);
        void key_handler(const SDL_KeyboardEvent& key);
        Game();
    
    private:
        std::vector<Rect> background;
};

#endif // _GAME_HPP_
