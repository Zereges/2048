#include <SDL.h>
#include <random>
#include <time.h>
#include <vector>
#include <string>
#include "../Program/Program.hpp"

// Starts the program. This is actualy replaced by SDL to handle C linakge.
int main(int argc, char* argv[])
{
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i)
        args.push_back(argv[i]);
    srand((unsigned) time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    int retvalue = Program::start(args);
    SDL_Quit();
    return retvalue;
}
