#ifndef _MERGE_HPP_
#define _MERGE_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Rect.hpp"
#include "Animation.hpp"

/*  
 *  Merge class handling animation of merging of blocks.
 */
class Merge : public Animation
{
    public:
        Merge(Rect& rect, int speed = Definitions::DEFAULT_MERGE_SPEED, int enlargement = Definitions::DEFAULT_MERGE_ENLARGEMENT) :
            Animation(&rect), m_point({rect.get_rect().x, rect.get_rect().y}), m_speed(speed)
        { m_size_x = rect.get_rect().w * enlargement/100; m_size_y = rect.get_rect().h * enlargement/100; }
        Merge(const Merge& m) : Animation(m.m_rect), m_point(m.m_point), m_speed(m.m_speed), m_size_x(m.m_size_x), m_size_y(m.m_size_y) { }
        Merge& operator=(const Merge&) = default;
        virtual ~Merge() = default;

        // Virtual method called when animation is required.
        // Merges m_rect at m_point position at m_speed speed.
        // Returns: true if animation is finished, false otherwise.
        virtual bool animate();

    private:
        int m_speed;
        SDL_Point m_point;
        std::size_t m_size_x, m_size_y;

        bool merge_animate();
};


#endif // _MERGE_HPP_
