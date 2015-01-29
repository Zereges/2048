#ifndef _RECT_HPP_
#define _RECT_HPP_
#include <SDL.h>
#include <memory> // size_t
#include "../Definitions/Definitions.hpp"
#include "../Definitions/Color.hpp"

/*  
 *  Wrapper around SDL_Rect with coloring posibility.
 */
class Rect
{
    public:
        Rect() : m_rect({ 0, 0, Definitions::BLOCK_SIZE_X, Definitions::BLOCK_SIZE_Y }), m_color() { }
        Rect(const SDL_Rect& rect, const Color& color) : m_rect(rect), m_color(color) { }
        Rect(std::size_t x, std::size_t y, const Color& color,
             std::size_t w = Definitions::BLOCK_SIZE_X, std::size_t h = Definitions::BLOCK_SIZE_Y) : Rect({x, y, w, h}, color) { }
        Rect(const SDL_Point& point, const Color& color, std::size_t w = Definitions::BLOCK_SIZE_X,
             std::size_t h = Definitions::BLOCK_SIZE_Y) : Rect(point.x, point.y, color, w, h) { }
        virtual ~Rect() { }
        const SDL_Rect& get_rect() const { return m_rect; }
        SDL_Rect& get_rect() { return m_rect; }
        const Color& get_color() const { return m_color; }
        virtual void draw() const;

    protected:
        SDL_Rect m_rect;
        Color m_color;
};

#endif // _RECT_HPP_
