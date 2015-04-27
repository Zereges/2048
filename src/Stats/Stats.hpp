#ifndef _STATS_HPP_
#define _STATS_HPP_
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "../Definitions/Definitions.hpp"
#include "../Window/Window.hpp"

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
    MAXIMAL_BLOCK,

    MAX_STATS,
};

class Stats
{
    public:
        // Zero statistics used as base of single game.
        Stats() : m_stats(MAX_STATS, 0l) { }

        // Global statistics loaded from given file.
        Stats(const std::string& file_name, const Window& window);
        
        Stats(const Stats&) = default;
        Stats& operator=(const Stats&) = default;
        Stats(Stats&& s) : m_stats(std::move(s.m_stats)) {  }

        // Calculates sum of stats into left operand.
        // Returns: Reference to summed stats.
        Stats& operator+=(const Stats& stats)
        {
            for (int i = 0; i < StatTypes::MAX_STATS; ++i)
                switch (i)
                {
                case StatTypes::HIGHEST_SCORE:
                case StatTypes::MAXIMAL_BLOCK:
                    m_stats[i] = std::max(m_stats[i], stats.m_stats[i]);
                    break;
                default:
                    m_stats[i] += stats.m_stats[i];
                }

            return *this;
        }

        // Statistics increments.
        void play(Directions dir);
        void move() { ++m_stats[StatTypes::BLOCKS_MOVED]; }
        void merge() { ++m_stats[StatTypes::BLOCKS_MERGED]; }
        void restart(time_t start_time) { ++m_stats[StatTypes::GAME_RESTARTS]; time_played(start_time); }
        void win(time_t start_time) { ++m_stats[StatTypes::GAME_WINS]; time_played(start_time); }
        void lose(time_t start_time) { ++m_stats[StatTypes::GAME_LOSES]; time_played(start_time); }
        void score(int score) { m_stats[StatTypes::TOTAL_SCORE] += score; }
        void update_time(time_t diff) { m_stats[StatTypes::TOTAL_TIME_PLAYED] += diff; }
        void highest_score(long long score) { m_stats[StatTypes::HIGHEST_SCORE] = std::max(score, m_stats[StatTypes::HIGHEST_SCORE]); }
        void maximal_block(long long number) { m_stats[StatTypes::MAXIMAL_BLOCK] = std::max(number, m_stats[StatTypes::MAXIMAL_BLOCK]); }

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

        // Attempts to save stats to given stream.
        friend std::ostream& operator<<(std::ostream& str, const Stats& stats)
        {
            for (std::size_t i = 0; i < StatTypes::MAX_STATS; ++i)
            {
                str << stats.m_stats[i] << " ";
            }
            return str;
        }

        // Sums two stats into new one.
        friend Stats operator+(const Stats& stats1, const Stats& stats2)
        {
            Stats s(stats1);
            s += stats2;
            return std::move(s);
        }

    private:
        std::vector<long long int> m_stats;
        static const std::vector<std::string> STATS_NAMES;

        inline void time_played(time_t start_time) { m_stats[StatTypes::TOTAL_TIME_PLAYED] += (time(0) - start_time); }
};



#endif // _STATS_HPP_