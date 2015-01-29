#ifndef _MOVEMENT_HPP_
#define _MOVEMENT_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Rect.hpp"

/*  
 *  Movement class handling moving of its contents.
 */
class Movement
{
    public:
        Movement(Rect& rect, Directions direction, const SDL_Point& point, int speed = Definitions::DEFAULT_MOVE_SPEED) :
            m_rect(rect), m_direction(direction), m_point(point), m_speed(speed) { }

        /*
         * Moves m_rect in m_direction to m_point at m_speed.
         * Returns: true if movement is completed, false otherwise.
         */
        bool move()
        {
            SDL_Rect& rect = m_rect.get_rect();
            switch (m_direction)
            {
                case LEFT: rect.x -= m_speed; break;
                case RIGHT: rect.x += m_speed; break;
                case UP: rect.y -= m_speed; break;
                case DOWN: rect.y += m_speed; break;
            }
            if (rect.x == m_point.x && rect.y == m_point.y)
                return true;
            return false;
        }

    private:
        Rect& m_rect;
        SDL_Point m_point;
        Directions m_direction;
        int m_speed;
};


#endif // _MOVEMENT_HPP_
