#include "Stats.hpp"
#include <fstream>
#include "..\Definitions\Definitions.hpp"

Stats::Stats(std::string file_name) : m_stats(StatTypes::MAX_STATS, 0l)
{
    std::ifstream file(file_name);
    // if file exists
    for (int i = 0; i < StatTypes::MAX_STATS; ++i)
    {
        file >> m_stats[i];
        // try catch whatever
    }
}

void Stats::play(Directions dir)
{
    switch (dir)
    {
        case LEFT: ++m_stats[StatTypes::LEFT_MOVES]; break;
        case RIGHT: ++m_stats[StatTypes::RIGHT_MOVES]; break;
        case UP: ++m_stats[StatTypes::UP_MOVES]; break;
        case DOWN: ++m_stats[StatTypes::DOWN_MOVES]; break;
    }
}
