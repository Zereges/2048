#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
/*  
 *  Game class handling user events.
 */
class Game
{
    public:
        void event_handler(const SDL_Event& event);
        void key_handler(const SDL_KeyboardEvent& key);
    
    private:

};

#endif // _GAME_HPP_
