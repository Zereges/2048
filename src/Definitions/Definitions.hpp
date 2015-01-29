#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_
#include <string>
#include <math.h>
#include <vector>

class Rect;
struct Color;

typedef std::vector<Rect> Rects;

/*  
 *  Abstract class containing definitions used throughout the program.
 */
class Definitions
{
    public:
        static const std::string WINDOW_NAME;           // Window name.
        static const std::size_t WINDOW_WIDTH;          // Total window width.
        static const std::size_t WINDOW_HEIGHT;         // Total window height.

        static const std::size_t GAME_X;                // X-Coord where Game begins.
        static const std::size_t GAME_Y;                // Y-Coord where Game begins.

        static const std::size_t GAME_WIDTH;            // Game width.
        static const std::size_t GAME_HEIGHT;           // Game height.

        static const std::size_t BLOCK_COUNT_X;         // Number of blocks in each horizontal line.
        static const std::size_t BLOCK_COUNT_Y;         // Number of blocks in each vertical line.
        static const std::size_t BLOCK_SIZE_X;          // Horizontal size of a single block. 
        static const std::size_t BLOCK_SIZE_Y;          // Vertical size of a single block.
        static const std::size_t BLOCK_SPACE;           // Space between blocks.
        static const std::vector<Color> BLOCK_COLORS;   // Colors of blocks based on their values.

        static const Color BACKGROUND_COLOR;            // Background color of window.

    private:
        Definitions() = delete; // To make it abstract
        Definitions(const Definitions&) = delete;
};

inline unsigned int logb(unsigned int val)
{
    return (unsigned int) trunc(log2(val));
}

#endif // _DEFINITIONS_HPP_
