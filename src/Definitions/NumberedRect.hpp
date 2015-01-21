#ifndef _NUMBEREDRECT_HPP_
#define _NUMBEREDRECT_HPP_
#include <SDL.h>
#include "Rect.hpp"

/*  
 *  Rect with number in it.
 */
class NumberedRect : public Rect
{
    public:
        NumberedRect(const SDL_Point& point, unsigned int number, std::size_t w = Definitions::BLOCK_SIZE_X, std::size_t h = Definitions::BLOCK_SIZE_Y)
        {
            m_rect = { point.x, point.y, w, h };
            auto i = logb(number) < Definitions::BLOCK_COLORS.size() ? logb(number) : Definitions::BLOCK_COLORS.size() - 1;
            m_color = Definitions::BLOCK_COLORS[i];
        }
        virtual ~NumberedRect() { }
        unsigned int get_number() { return m_number; }
        virtual void draw() const;

    private:
        unsigned int m_number;
};

#endif // _NUMBEREDRECT_HPP_
