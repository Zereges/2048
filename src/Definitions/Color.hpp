#ifndef _COLOR_HPP_
#define _COLOR_HPP_
#include "Definitions.hpp"
#include <algorithm>
/*  
 *  Struct for saving RGBA-Color, values > 255 does not make sense and will be ignored by rendering mechanisms.
 */
struct Color
{
    uint r, g, b, a;
    Color(uint _r, uint _g, uint _b, uint _a) : r(_r), g(_g), b(_b), a(_a) { }
    Color(uint _r, uint _g, uint _b) : Color(_r, _g, _b, 255) { }
};

#endif // _COLOR_HPP_
