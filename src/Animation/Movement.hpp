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
        Movement(Rect& rect, const SDL_Point& point, int speed = Definitions::DEFAULT_MOVE_SPEED) :
            m_rect(&rect), m_point(point), m_speed(speed) {  }
        Movement(const Movement& m) : m_rect(m.m_rect), m_point(m.m_point), m_speed(m.m_speed) { }
        Movement& operator=(const Movement& m) { m_rect = m.m_rect; m_point = m.m_point; m_speed = m.m_speed; return *this; }

        /*
         * Moves m_rect in m_direction to m_point at m_speed.
         * Returns: true if movement is completed, false otherwise.
         */
        bool move();

    private:
        Rect* m_rect;
        SDL_Point m_point;
        int m_speed;
};


#endif // _MOVEMENT_HPP_
