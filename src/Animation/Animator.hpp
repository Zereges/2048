#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include <algorithm>
#include "..\Definitions\Definitions.hpp"
#include "..\Definitions\Rect.hpp"
#include "Movement.hpp"

/*  
 *  Animation class handles procession of Moving of Rects.
 */
class Animator
{
    public:
        void add_movement(Rect& rect, Directions direction, const SDL_Point& point, int speed = Definitions::DEFAULT_MOVE_SPEED)
            { m_movement.push_back(Movement(rect, direction, point, speed)); }
        void animate()
        {
            // std::remove_if(begin(m_movement), end(m_movement), [](Movement m) { return m.move(); });
        }

    private:
        std::vector<Movement> m_movement;
};


#endif // _ANIMATION_HPP_
