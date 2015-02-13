#ifndef _NUMBEREDRECT_HPP_
#define _NUMBEREDRECT_HPP_
#include <SDL.h>
#include "Definitions.hpp"
#include "Rect.hpp"

/*  
 *  Rect with number in it.
 */
class NumberedRect : public Rect
{
    public:
        NumberedRect(const SDL_Point& point, unsigned int number, std::size_t w = Definitions::BLOCK_SIZE_X, std::size_t h = Definitions::BLOCK_SIZE_Y) :
            Rect(point, Definitions::BLOCK_COLORS[logb(number)], w, h) { }
        virtual ~NumberedRect() { }
        unsigned int get_number() { return m_number; }
        virtual void draw() const { Rect::draw(); }

    private:
        unsigned int m_number;
};

#endif // _NUMBEREDRECT_HPP_
