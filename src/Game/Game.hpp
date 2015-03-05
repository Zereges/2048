#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
#include <vector>
#include <exception>
#include "..\Definitions\Definitions.hpp"
#include "..\Definitions\Rect.hpp"
#include "..\Definitions\NumberedRect.hpp"
#include "..\Animation\Animator.hpp"
/*  
 *  Game class handling user events.
 */
class Game
{
    public:
        Game();
        // SDL_Event handler.
        // Params: event - SDL_Event to process.
        void event_handler(const SDL_Event& event);

        // SDL_KeyboardEvent handler.
        // Params: key - SDL_KeyboardEvent to process.
        void key_handler(const SDL_KeyboardEvent& key);

        // Returns reference to vector of Rects used in background.
        // Returns: reference to m_background.
        const Rects& get_background() const { return m_background; }

        // Returns reference to vector of NumberedRects used on game field.
        // Returns: reference to m_rects.
        const NumberedRects& get_rects() const { return m_rects; }

        // Computes real x and y coords for given params.
        // Params: x - x coord on game field (0 <= x < Definitions::BLOCK_COUNT_X)
        //         y - y coord on game field (0 <= y < Definitions::BLOCK_COUNT_Y)
        // Returns: SDL_Point containing computed coords.
        static SDL_Point get_block_coords(unsigned int x, unsigned int y)
        {
            if (x < 0 || x >= Definitions::BLOCK_COUNT_X || y < 0 || y >= Definitions::BLOCK_COUNT_Y)
                throw std::runtime_error("Invalid coords for Game::get_block_coords(unsigned, unsigned)");
            return { Definitions::GAME_X + Definitions::BLOCK_SPACE + x * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X),
                     Definitions::GAME_Y + Definitions::BLOCK_SPACE + y * (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)
                   };
        }

        // Computes game-field coords on which given Rect exists.
        // Params: rect - Rect which coords will be computed.
        // Returns: std::pair<int, int> of game-field coords.
        static std::pair<int, int> get_coords_block(const Rect& rect)
        {
            return {(rect.get_rect().x - Definitions::GAME_X - Definitions::BLOCK_SPACE) / (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_X), 
                    (rect.get_rect().y - Definitions::GAME_Y - Definitions::BLOCK_SPACE) / (Definitions::BLOCK_SPACE + Definitions::BLOCK_SIZE_Y)};
        }

        // Starts new game.
        void start();

        // Calls animate of Animator
        void animate() { m_animator.animate(); }

        // Checks whether player can play.
        // Returns: true if can, false otherwise.
        bool can_play() { return m_animator.can_play(); }

        // Processes player's turn.
        // Params: direction - Direction which player decided to play.
        void play(Directions direction);

        // Inserts random block on board and updates state.
        // Params: block - Block to insert
        // Returns: true on success, false on failure (full board, can't play)
        bool random_block(Blocks block);

        // Removes all progress in current game and starts new one.
        void restart();

        // Is called when after player's turn is processed.
        void on_turn_end();

    private:
        Rects m_background;    // Rectangles which forms a background of game.
        NumberedRects m_rects; // Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y field of NumberedRectangles forming state of a game.
        Animator m_animator;   // Animator class handling movement animtions.

        // Passes movement request to animator class.
        // Params: rect - NumberedRect to move.
        //         x - x coord where to move.
        //         y - y coord where to move.
        void move_to(NumberedRect& rect, std::size_t x, std::size_t y);
};

#endif // _GAME_HPP_
