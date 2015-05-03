#ifndef _RECT_HPP_
#define _RECT_HPP_
#include <SDL.h>
#include <memory> // size_t
#include "../Definitions/Definitions.hpp"
#include "../Window/Window.hpp"

/*  
 *  SDL_Rect wrapper with coloring posibility.
 */
class Rect
{
    public:
        Rect(const SDL_Rect& rect, const SDL_Color& color) : m_rect(rect), m_color(color) { }
        Rect(std::size_t x, std::size_t y, const SDL_Color& color, std::size_t w = Definitions::BLOCK_SIZE_X, std::size_t h = Definitions::BLOCK_SIZE_Y) :
            Rect({x, y, w, h}, color) { }

        Rect(const SDL_Point& point, const SDL_Color& color, std::size_t w = Definitions::BLOCK_SIZE_X, std::size_t h = Definitions::BLOCK_SIZE_Y) :
            Rect({point.x + (Definitions::BLOCK_SIZE_X - w) / 2, point.y + (Definitions::BLOCK_SIZE_Y - h) / 2, w, h}, color) { }

        virtual ~Rect() = default;
        SDL_Rect& get_rect() { return m_rect; }
        const SDL_Rect& get_rect() const { return m_rect; }
        virtual void draw(Window& window) const;

    protected:
        SDL_Rect m_rect;
        SDL_Color m_color;
};

#endif // _RECT_HPP_
