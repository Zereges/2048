#include <SDL.h>
#include "../Program/Program.hpp"

// Starts the program. This is actualy replaced by SDL to handle C linakge.
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    int retvalue = Program::start();
    SDL_Quit();
    return retvalue;
}
