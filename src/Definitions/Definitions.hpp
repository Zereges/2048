#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_
#include <string>
#include "Color.hpp"
/*  
 *  Abstract class containing definitions used throughout the program.
 */
class Definitions
{
    public:
        static const std::string WINDOW_NAME;
        static const std::size_t WINDOW_WIDTH;
        static const std::size_t WINDOW_HEIGHT;

        static const std::size_t GAME_X;
        static const std::size_t GAME_Y;

        static const std::size_t GAME_WIDTH;
        static const std::size_t GAME_HEIGHT;

        static const std::size_t BLOCK_COUNT_X;
        static const std::size_t BLOCK_COUNT_Y;
        static const std::size_t BLOCK_SIZE_X;
        static const std::size_t BLOCK_SIZE_Y;
        static const std::size_t BLOCK_SPACE;
        static const Color BLOCK_COLOR;

        static const Color BACKGROUND_COLOR;

    private:
        Definitions() = delete; // To make it abstract
};

#endif // _DEFINITIONS_HPP_
