#ifndef _RECT_HPP_
#define _RECT_HPP_
#include <SDL.h>
#include "Color.hpp"

/*  
 *  Wrapper around SDL_Rect with coloring posibility.
 */
struct Rect
{
    public:
        Rect(const SDL_Rect& _rect, const Color& _color) : rect(_rect), color(_color) { }
        Rect(std::size_t x, std::size_t y, std::size_t w, std::size_t h, const Color& _color) : Rect({x, y, w, h}, _color) { }
        const SDL_Rect& get_rect() const { return rect; }
        const Color& get_color() const { return color; }

    private:
        SDL_Rect rect;
        Color color;
};

#endif // _RECT_HPP_
