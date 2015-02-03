#include "Definitions.hpp"
#include "Color.hpp"
const std::string Definitions::WINDOW_NAME = "2048 Game";
const std::size_t Definitions::WINDOW_WIDTH = GAME_WIDTH;
const std::size_t Definitions::WINDOW_HEIGHT = GAME_HEIGHT;

const std::size_t Definitions::GAME_X = 0;
const std::size_t Definitions::GAME_Y = 0;
const std::size_t Definitions::GAME_WIDTH = BLOCK_COUNT_X * BLOCK_SIZE_X + (BLOCK_COUNT_X + 1) * BLOCK_SPACE;
const std::size_t Definitions::GAME_HEIGHT = BLOCK_COUNT_Y * BLOCK_SIZE_Y + (BLOCK_COUNT_Y + 1) * BLOCK_SPACE;

const std::size_t Definitions::BLOCK_COUNT_X = 4;
const std::size_t Definitions::BLOCK_COUNT_Y = BLOCK_COUNT_X; // Works even if not symetrical.
const std::size_t Definitions::BLOCK_SIZE_X = 400 / BLOCK_COUNT_X;
const std::size_t Definitions::BLOCK_SIZE_Y = 400 / BLOCK_COUNT_Y;
const std::size_t Definitions::BLOCK_SPACE = 15;
const std::vector<Color> Definitions::BLOCK_COLORS = {
    Color(85, 85, 85),    // default empty
    Color(153, 171, 174), // 2
};

const Color Definitions::BACKGROUND_COLOR = Color(30, 30, 30);

const int Definitions::DEFAULT_MOVE_SPEED = 5;
