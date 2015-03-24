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
            Rect(point, Definitions::BLOCK_COLORS[number], w, h) { m_number = number; }
        virtual ~NumberedRect() { }

        // Gets number representing value of NumberedRect.
        // Returns: number representing value of NumberedRect.
        unsigned int get_number() const { return m_number; }
        
        // Increments number of NumberedRect to next value.
        void next_number() { m_color = Definitions::BLOCK_COLORS[++m_number]; }
        virtual void draw() const { Rect::draw(); }

    private:
        unsigned int m_number;
};

#endif // _NUMBEREDRECT_HPP_
