#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <math.h>
#include <vector>
#include <memory>
class Rect;
class NumberedRect;

typedef std::vector<Rect> Rects;
typedef std::vector<std::vector<std::shared_ptr<NumberedRect> > > NumberedRects;

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
    BLOCK_131072, // Max on 4x4

    MAX_BLOCKS,
};

/*  
 *  Abstract class containing definitions used throughout the program.
 */
class Definitions
{
    public:
        static const std::string WINDOW_NAME;                           // Window name.
        static const std::size_t WINDOW_WIDTH;                          // Total window width.
        static const std::size_t WINDOW_HEIGHT;                         // Total window height.

        static const std::size_t GAME_X;                                // X-Coord where Game begins.
        static const std::size_t GAME_Y;                                // Y-Coord where Game begins.

        static const std::size_t GAME_WIDTH;                            // Game width.
        static const std::size_t GAME_HEIGHT;                           // Game height.

        static const std::size_t BLOCK_COUNT_X;                         // Number of blocks in each horizontal line.
        static const std::size_t BLOCK_COUNT_Y;                         // Number of blocks in each vertical line.
        static const std::size_t BLOCK_SIZE_X;                          // Horizontal size of a single block. 
        static const std::size_t BLOCK_SIZE_Y;                          // Vertical size of a single block.
        static const std::size_t BLOCK_SPACE;                           // Space between blocks.
        static const std::vector<SDL_Color> BLOCK_COLORS;               // Colors of blocks based on their values.

        static const SDL_Color BACKGROUND_COLOR;                        // Background color of the window.

        static const int DEFAULT_MOVE_SPEED;                            // Default move speed of blocks in pixels per frame
        static const int DEFAULT_SPAWN_SPEED;                           // Default spawn speed of blocks in pixels per frame
        static const int DEFAULT_MERGE_SPEED;                           // Default merge speed of blocks in pixels per frame
        static const int DEFAULT_MERGE_ENLARGEMENT;                     // Default percentual enlargement of merged block.

        static const int BLOCK_4_SPAWN_CHANCE;                          // Chance of spawning BLOCK_4 instead of BLOCK_2
        static const int DEFAULT_START_BLOCKS;                          // Blocks given to player at start.

        static const SDL_Color DEFAULT_BLOCK_FONT_COLOR;                // Default font color used in blocks' numbers.
        static const std::string Definitions::DEFAULT_BLOCK_FONT_NAME;  // Default font name used in blocks'numbers.
        
        static SDL_Color get_block_color(unsigned int number) { return number < BLOCK_COLORS.size() ? BLOCK_COLORS[number] : BLOCK_COLORS[BLOCK_COLORS.size() - 1]; }


    private:
        Definitions() = delete; // To make it abstract
        Definitions(const Definitions&) = delete;
        Definitions(Definitions&&) = delete;
        Definitions& operator=(const Definitions&) = delete;
        Definitions& operator=(Definitions&&) = delete;
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
