#ifndef _MOVE_HPP_
#define _MOVE_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Rect.hpp"
#include "Animation.hpp"

/*  
 *  Move class handling animation of moving of blocks.
 */
class Move : public Animation
{
    public:
        Move(Rect& rect, const SDL_Point& point, int speed = Definitions::DEFAULT_MOVE_SPEED) :
            Animation(&rect), m_point(point), m_speed(speed) { }
        Move(const Move& m) : Animation(m.m_rect), m_point(m.m_point), m_speed(m.m_speed) { }
        Move& operator=(const Move&) = default;
        virtual ~Move() = default;

        // Virtual method called when animation is required.
        // Moves m_rect to m_point at m_speed.
        // Returns: true if animation is finished, false otherwise.
        virtual bool animate();

    private:
        SDL_Point m_point;
        int m_speed;
};


#endif // _MOVE_HPP_
