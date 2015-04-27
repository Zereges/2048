#include <SDL.h>
#include "GameWindow.hpp"
#include "../Game/Game.hpp"

void GameWindow::add(const Rects& objects)
{
    for (auto iter = std::begin(objects); iter != std::end(objects); ++iter)
        iter->draw(*this);
}

void GameWindow::add(const NumberedRects& objects)
{
    for (auto iter = begin(objects); iter != end(objects); ++iter)
        for (auto jter = begin(*iter); jter != end(*iter); ++jter)
            if (*jter != nullptr)
                (*jter)->draw(*this);
}
