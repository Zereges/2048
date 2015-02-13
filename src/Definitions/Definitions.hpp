#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_
#include <string>
#include <math.h>
#include <vector>

class Rect;
class NumberedRect;
struct Color;

typedef std::vector<Rect> Rects;
typedef std::vector<NumberedRect> NumberedRects;
typedef std::vector<std::vector<const Rect*>> State;

enum Directions
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

enum Blocks
{
    BLOCK_2 = 1,
    BLOCK_4,
    BLOCK_8,
    BLOCK_16,
    BLOCK_32,
    BLOCK_64,
    BLOCK_128,
    BLOCK_256,
    BLOCK_512,
    BLOCK_1024,
    BLOCK_2048,
    BLOCK_4096,
    BLOCK_8192,
    BLOCK_16384,
    BLOCK_32768,
    BLOCK_65536,
    BLOCK_131072,
};

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

        static const int DEFAULT_MOVE_SPEED;            // Default move speed of blocks in pixels per frame

        static const int BLOCK_4_SPAWN_CHANCE;          // Chance of spawning BLOCK_4 instead of BLOCK_2
        static const int DEFAULT_START_BLOCKS;          // Blocks given to player at start.

    private:
        Definitions() = delete; // To make it abstract
        Definitions(const Definitions&) = delete;
};

inline unsigned int logb(unsigned int val)
{
    return (unsigned int) trunc(log2(val));
}

inline bool chance(int c)
{
    return rand() % 100 < c;
}

#endif // _DEFINITIONS_HPP_
