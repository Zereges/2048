#ifndef _COLOR_HPP_
#define _COLOR_HPP_
#include <SDL.h>
/*  
 *  Struct for saving RGBA-Color, values > 255 does not make sense and will be ignored by rendering mechanisms.
 */
struct Color
{
    unsigned int r, g, b, a;

    Color(unsigned int _r = 0, unsigned int _g = 0, unsigned int _b = 0, unsigned int _a = SDL_ALPHA_OPAQUE) : r(_r), g(_g), b(_b), a(_a) { }
};

#endif // _COLOR_HPP_
