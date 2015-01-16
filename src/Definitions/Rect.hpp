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
        SDL_Rect& get_rect() { return rect; }
        Color& get_color() { return color; }

    private:
        SDL_Rect rect;
        Color color;
};

#endif // _RECT_HPP_
