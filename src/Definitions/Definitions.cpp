#include "Definitions.hpp"
#include "Color.hpp"
const std::string Definitions::WINDOW_NAME = "2048 Game";
const std::size_t Definitions::WINDOW_WIDTH = GAME_WIDTH;
const std::size_t Definitions::WINDOW_HEIGHT = GAME_HEIGHT;

const std::size_t Definitions::BLOCK_COUNT_X = 4;
const std::size_t Definitions::BLOCK_COUNT_Y = BLOCK_COUNT_X; // Works even if not symetrical.
const std::size_t Definitions::BLOCK_SIZE_X = 400 / BLOCK_COUNT_X;
const std::size_t Definitions::BLOCK_SIZE_Y = 400 / BLOCK_COUNT_Y;
const std::size_t Definitions::BLOCK_SPACE = 15;

const std::size_t Definitions::GAME_X = 0;
const std::size_t Definitions::GAME_Y = 0;
const std::size_t Definitions::GAME_WIDTH = GAME_X + BLOCK_COUNT_X * BLOCK_SIZE_X + (BLOCK_COUNT_X + 1) * BLOCK_SPACE;
const std::size_t Definitions::GAME_HEIGHT = GAME_Y + BLOCK_COUNT_Y * BLOCK_SIZE_Y + (BLOCK_COUNT_Y + 1) * BLOCK_SPACE;

const std::vector<Color> Definitions::BLOCK_COLORS = {
    Color( 85,  85,  85), // default empty
    Color(153, 171, 174), // BLOCK_2
    Color( 47, 119,  80), // BLOCK_4
    Color( 58, 133,  33), // BLOCK_8
    Color(130, 146,  20), // BLOCK_16
    Color(156, 105,  10), // BLOCK_32
    Color(166,  41,   0), // BLOCK_64
};

const Color Definitions::BACKGROUND_COLOR = Color(30, 30, 30);

const int Definitions::DEFAULT_MOVE_SPEED = 3;
const int Definitions::DEFAULT_SPAWN_SPEED = 1;
const int Definitions::DEFAULT_MERGE_SPEED = DEFAULT_SPAWN_SPEED;
const int Definitions::BLOCK_4_SPAWN_CHANCE = 15;
const int Definitions::DEFAULT_START_BLOCKS = 2;
const int Definitions::DEFAULT_MERGE_ENLARGEMENT = 150;
