#ifndef _SPAWN_HPP_
#define _SPAWN_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Rect.hpp"
#include "Animation.hpp"

/*  
 *  Spawn class handling animation of spawning of new blocks.
 */
class Spawn : public Animation
{
    public:
        Spawn(Rect& rect, const SDL_Point& point, std::size_t size_x = Definitions::BLOCK_SIZE_X,
            std::size_t size_y = Definitions::BLOCK_SIZE_X, int speed = Definitions::DEFAULT_SPAWN_SPEED) :
            Animation(&rect), m_point(point), m_size_x(size_x), m_size_y(size_y), m_speed(speed) { }
        Spawn(const Spawn& s) : Animation(s.m_rect), m_size_x(s.m_size_x), m_size_y(s.m_size_y), m_speed(s.m_speed), m_point(s.m_point) { }
        Spawn& operator=(const Spawn&) = default;
        virtual ~Spawn() = default;

        // Virtual method called when animation is required.
        // Enlarges m_rect to m_size_x * m_size_y size at m_speed.
        // Returns: true if animation is finished, false otherwise.
        virtual bool animate();

    private:
        int m_speed;
        std::size_t m_size_x, m_size_y;
        SDL_Point m_point;
};


#endif // _SPAWN_HPP_
