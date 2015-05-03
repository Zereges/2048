#ifndef _NUMBEREDRECT_HPP_
#define _NUMBEREDRECT_HPP_
#include <SDL.h>
#include <unordered_map>
#include "Definitions.hpp"
#include "Rect.hpp"
#include "../Window/Window.hpp"

/*  
 *  Rect with number in it.
 */
class NumberedRect : public Rect
{
    public:
        NumberedRect(const SDL_Point& point, Blocks block, std::size_t width = Definitions::BLOCK_SIZE_X, std::size_t height = Definitions::BLOCK_SIZE_Y) :
            Rect(point, Definitions::get_block_color(block), width, height), m_number(block) { }
        virtual ~NumberedRect() = default;

        // Gets number representing value of NumberedRect.
        // Returns: number representing value of NumberedRect.
        unsigned int get_number() const { return m_number; }
        
        // Increments number of NumberedRect to next value.
        // Returns: Real shown number.
        int next_number() { m_color = Definitions::get_block_color(++m_number); return pow2(m_number); }
        virtual void draw(Window& window) const;

        // Initializes SDL_Textures with Block numbers.
        // Params: window - reference to Window class, for which Renderer will be used.
        //         number - number to create.
        //         font   - pointer to font used.
        static void init_number(Window& window, unsigned int number, TTF_Font* font = nullptr);
        static void init_numbers(Window& window);

        // Frees contents of NUMBERS.
        static void destroy_numbers() { for (auto iter = NUMBERS.begin(); iter != NUMBERS.end(); ++iter) SDL_DestroyTexture(iter->second); }

    private:
        Blocks m_number;
        static std::unordered_map<std::size_t, SDL_Texture*> NUMBERS;
};

#endif // _NUMBEREDRECT_HPP_
