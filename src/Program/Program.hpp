#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_
#include <vector>
#include <string>
/*  
 *  Static class for handling program and SDL events.
 */
class Program
{
    public:
        static int start(const std::vector<std::string>& args);
        static bool is_running() { return m_is_running; }
        static void stop(bool force);

    private:
        static bool m_is_running;
        static int m_ret_value;

        // Disallow creation of instances
        Program() = delete;
        Program(Program&) = delete;
        Program(Program&&) = delete;
        Program& operator=(Program&) = delete;
        Program& operator=(Program&&) = delete;
};

#endif // _PROGRAM_HPP_
