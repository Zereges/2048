#ifndef _MOVEMENT_HPP_
#define _MOVEMENT_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Rect.hpp"
#include "Animation.hpp"

/*  
 *  Movement class handling moving of its contents.
 */
class Movement : public Animation
{
    public:
        Movement(Rect& rect, const SDL_Point& point, int speed = Definitions::DEFAULT_MOVE_SPEED) :
            Animation(&rect), m_point(point), m_speed(speed) { }
        Movement(const Movement& m) : Animation(m.m_rect), m_point(m.m_point), m_speed(m.m_speed) { }
        Movement& operator=(const Movement& m) { m_rect = m.m_rect; m_point = m.m_point; m_speed = m.m_speed; return *this; }
        virtual ~Movement() = default;

        // Virtual method called when animation is required.
        // Moves m_rect to m_point at m_speed.
        // Returns: true if animation is finished, false otherwise.
        virtual bool animate();

    private:
        SDL_Point m_point;
        int m_speed;
};


#endif // _MOVEMENT_HPP_
