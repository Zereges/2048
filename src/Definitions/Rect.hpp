#ifndef _RECT_HPP_
#define _RECT_HPP_
#include <SDL.h>
#include "Color.hpp"
#include <memory> // size_t

/*  
 *  Wrapper around SDL_Rect with coloring posibility.
 */
class Rect
{
    public:
        Rect(const SDL_Rect& rect, const Color& color) : m_rect(rect), m_color(color) { }
        Rect(std::size_t x, std::size_t y, std::size_t w, std::size_t h, const Color& color) : Rect({x, y, w, h}, color) { }
        const SDL_Rect& get_rect() const { return m_rect; }
        const Color& get_color() const { return m_color; }
        virtual void draw() const;
        virtual ~Rect() { }

    private:
        SDL_Rect m_rect;
        Color m_color;
};

#endif // _RECT_HPP_
