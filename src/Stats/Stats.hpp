#ifndef _STATS_HPP_
#define _STATS_HPP_
#include <vector>
#include <string>
#include <fstream>
#include "..\Definitions\Definitions.hpp"
enum StatTypes
{
    LEFT_MOVES = 0,
    RIGHT_MOVES,
    UP_MOVES,
    DOWN_MOVES,
    BLOCKS_MOVED,
    BLOCKS_MERGED,
    GAME_RESTARTS,

    MAX_STATS,
};

class Stats
{
    public:
        // Zero statistics used as base of single game.
        Stats() : m_stats(MAX_STATS, 0l) { }

        // Global statistics loaded from given file.
        Stats(std::string file_name);
        
        // Calculates sum of stats into left operand.
        // Returns: Reference to summed stats.
        Stats& operator+=(const Stats& stats) { for (int i = 0; i < StatTypes::MAX_STATS; ++i) m_stats[i] += stats.m_stats[i]; return *this; }

        void play(Directions dir);
        void move() { ++m_stats[StatTypes::BLOCKS_MOVED]; }
        void merge() { ++m_stats[StatTypes::BLOCKS_MERGED]; }
        void restart() { ++m_stats[StatTypes::GAME_RESTARTS]; }

    private:
        std::vector<long long int> m_stats;
};

#endif // _STATS_HPP_