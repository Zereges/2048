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
        typedef std::vector<Rect> Objects;

        void event_handler(const SDL_Event& event);
        void key_handler(const SDL_KeyboardEvent& key);
        const Objects& get_background() const { return background; }
        Game();
    
    private:
        Objects background;
};

#endif // _GAME_HPP_
