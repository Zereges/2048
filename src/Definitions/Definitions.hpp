#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_
#include <string>


/*  
 *  Abstract class containing definitions used throughout the program.
 */
class Definitions
{
    public:
        static const std::string WINDOW_NAME;
        static const std::size_t WIDTH;
        static const std::size_t HEIGHT;

    private:
        Definitions() = delete; // To make it abstract
};

#endif // _DEFINITIONS_HPP_
