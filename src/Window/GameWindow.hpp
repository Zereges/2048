#ifndef _GAME_WINDOW_HPP_
#define _GAME_WINDOW_HPP_
#include <memory>
#include <SDL.h>
#include "Window.hpp"
#include "..\Definitions\Definitions.hpp"

/*
 *  Wrapper around SDL_Window and SDL_Renderer allowing creation and drawing rects on window.
 */
class GameWindow : public Window
{
    public:
        GameWindow(std::size_t width, std::size_t height, std::string name) : Window(width, height, name) { }
        void add(const Rects& background);
        void add(const NumberedRects& rects);
};

#endif // _GAME_WINDOW_HPP_
