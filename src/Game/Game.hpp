#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <SDL.h>
#include <vector>
#include <exception>
#include <iostream>
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
        bool can_play() const { return m_animator.can_play(); }

        // Processes player's turn.
        // Params: direction - Direction which player decided to play.
        void play(Directions direction);

        // Inserts block on given coords
        // Params: block - Block to insert.
        //         x - x coord
        //         y - y coord
        // Return: true on success, false on failure
        bool spawn_block(Blocks block, std::size_t x, std::size_t y);

        // Inserts random block on board.
        // Params: block - Block to insert. Default: BLOCK_4 with BLOCK_4_SPAWN_CHANCE, otherwise BLOCK_2.
        // Returns: true on success, false on failure (full board).
        bool random_block(Blocks block = chance(Definitions::BLOCK_4_SPAWN_CHANCE) ? BLOCK_4 : BLOCK_2);

        // Removes all progress in current game and starts new one.
        void restart();

        // Is called when after player's turn is processed.
        void on_turn_end();

        // Checks whether two NumberedRects can be merged together.
        // Params: r1 - NumberedRect 1 to check
        //         r2 - NumberedRect 2 to check
        // Returns: true if possible, false otherwise
        bool can_merge(const NumberedRect& r1, const NumberedRect& r2) const { return r1.get_number() == r1.get_number(); }

        // Checks whether two NumberedRects can be merged together.
        // Params: r1 - pointer to NumberedRect 1 to check
        //         r2 - pointer to NumberedRect 2 to check
        // Returns: true if possible, false otherwise
        bool can_merge(std::shared_ptr<NumberedRect> r1, std::shared_ptr<NumberedRect> r2) const
        {
            return r1 != nullptr && r2 != nullptr && r1->get_number() == r2->get_number();
        }
        

    private:
        Rects m_background;    // Rectangles which forms a background of game.
        NumberedRects m_rects; // Definitions::BLOCK_COUNT_X * Definitions::BLOCK_COUNT_Y field of NumberedRectangles forming state of a game.
        Animator m_animator;   // Animator class handling movement animtions.

        // Passes movement request to animator class and updates inner state.
        // Params: from_x - x coord of Rect on field.
        //         from_y - y coord of Rect on field.
        //         to_x - x coord where to move.
        //         to_y - y coord where to move.
        void move_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y);

        // Passes merge request to animator class and updates inner state.
        // Params: from_x - x coord of Rect on field.
        //         from_y - y coord of Rect on field.
        //         to_x - x coord of Rect to merge.
        //         to_y - y coord of Rect to merge.
        void merge_to(std::size_t from_x, std::size_t from_y, std::size_t to_x, std::size_t to_y);

        void dbg_print(bool verb = false)
        {
            for (unsigned int y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
            {
                for (unsigned int x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
                    std::cout << (m_rects[x][y] ? m_rects[x][y]->get_number() : 0) << " ";
                std::cout << std::endl;
            }
            if (verb)
                for (unsigned int y = 0; y < Definitions::BLOCK_COUNT_Y; ++y)
                    for (unsigned int x = 0; x < Definitions::BLOCK_COUNT_X; ++x)
                        if (m_rects[x][y])
                            std::cout << "(" << x << "," << y << "): " << m_rects[x][y]->get_rect().x << ", " << m_rects[x][y]->get_rect().y << std::endl;

            std::cout << std::endl;
        }
};

#endif // _GAME_HPP_
