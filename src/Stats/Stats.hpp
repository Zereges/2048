#ifndef _STATS_HPP_
#define _STATS_HPP_
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
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
    GAME_WINS,
    GAME_LOSES,
    TOTAL_TIME_PLAYED,
    TOTAL_SCORE,
    HIGHEST_SCORE,

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

        // Statistics increments.
        void play(Directions dir);
        void move() { ++m_stats[StatTypes::BLOCKS_MOVED]; }
        void merge() { ++m_stats[StatTypes::BLOCKS_MERGED]; }
        void restart(time_t start_time) { ++m_stats[StatTypes::GAME_RESTARTS]; time_played(start_time); }
        void win(time_t start_time) { ++m_stats[StatTypes::GAME_WINS]; time_played(start_time); }
        void lose(time_t start_time) { ++m_stats[StatTypes::GAME_LOSES]; time_played(start_time); }
        void score(int score) { m_stats[StatTypes::TOTAL_SCORE] += score; }
        void highest_score(long long score) { m_stats[StatTypes::HIGHEST_SCORE] = std::max(score, m_stats[StatTypes::HIGHEST_SCORE]); }

        // Returns string preformated for showing in Stats Window.
        // Returns: preformated string.
        std::string to_string() const;

        // Returns maximal length of value in statistics. Used for formating purposes.
        // Returns: max length.
        std::size_t max_value_size() const { return std::to_string(*std::max_element(std::begin(m_stats), std::end(m_stats))).size(); }

        // Returns maximal length of names in statistics. Used for formating purposes.
        // Returns: max length.
        std::size_t max_name_size() const
        {
            using const_reference = const std::iterator_traits<decltype(std::begin(STATS_NAMES))>::value_type&;
            return std::max_element(std::begin(STATS_NAMES), std::end(STATS_NAMES), [](const_reference s1, const_reference s2)
            {
                return s1.size() < s2.size();
            })->size();
        }

    private:
        std::vector<long long int> m_stats;
        static const std::vector<std::string> STATS_NAMES;

        inline void time_played(time_t start_time) { m_stats[StatTypes::TOTAL_TIME_PLAYED] += (time(0) - start_time); }
};



#endif // _STATS_HPP_