#include "Stats.hpp"
#include <iostream>
#include "..\Definitions\Definitions.hpp"

const std::vector<std::string> Stats::STATS_NAMES = {
    "Left moves", /* = 0*/
    "Right moves",
    "Up moves",
    "Down moves",
    "Blocks moved",
    "Blocks merged",
    "Game Restarts",
};

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

std::string Stats::to_string() const
{
    std::string result;
    for (int i = 0; i < StatTypes::MAX_STATS; ++i)
    {
        result += std::string(max_name_size() - STATS_NAMES[i].size(), ' ') + STATS_NAMES[i]
               +  Definitions::STATS_DELIMITER
               +  std::string(max_value_size() - std::to_string(m_stats[i]).size(), ' ') + std::to_string(m_stats[i])
               +  "\n";
    }
    
    return std::move(result);
}
