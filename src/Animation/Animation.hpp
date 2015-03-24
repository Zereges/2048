#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_
#include <SDL.h>
#include "../Definitions/Rect.hpp"
/*
 *  Interface for animating events throughout playthrough.
 */
class Animation
{
    public:
        virtual ~Animation() = default;

        // Virtual method called when animation is required.
        // Returns: true if animation is finished, false otherwise.
        virtual bool animate() = 0;
    protected:
        Animation(const Animation&) = default;
        Animation(Rect* rect) : m_rect(rect) { }
        Rect* m_rect;
};

#endif // _ANIMATION_HPP_