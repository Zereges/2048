#include <SDL.h>
#include "GameWindow.hpp"
#include "../Game/Game.hpp"

void GameWindow::add(const Rects& objects)
{
    for (auto iter = std::cbegin(objects); iter != std::cend(objects); ++iter)
        iter->draw(*this);
}

void GameWindow::add(const NumberedRects& objects)
{
    for (auto iter = cbegin(objects); iter != cend(objects); ++iter)
        for (auto jter = cbegin(*iter); jter != cend(*iter); ++jter)
            if (*jter != nullptr)
                (*jter)->draw(*this);
}
