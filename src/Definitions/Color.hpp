#ifndef _COLOR_HPP_
#define _COLOR_HPP_
#include <algorithm>
/*  
 *  Struct for saving RGBA-Color, values > 255 does not make sense and will be ignored by rendering mechanisms.
 */
struct Color
{
    unsigned int r, g, b, a;

    Color(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a) : r(_r), g(_g), b(_b), a(_a) { }
    Color(unsigned int _r, unsigned int _g, unsigned int _b) : Color(_r, _g, _b, 255) { }
};

#endif // _COLOR_HPP_