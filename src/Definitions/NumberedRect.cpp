#include "NumberedRect.hpp"

std::unordered_map<std::size_t, SDL_Texture*> NumberedRect::NUMBERS;

void NumberedRect::init_numbers()
{
    TTF_Font* font = TTF_OpenFont(Definitions::DEFAULT_BLOCK_FONT_NAME.c_str(), Definitions::BLOCK_SIZE_X);
    for (std::size_t i = 0; i < Blocks::MAX_BLOCKS; ++i)
    {
        init_number(i, font);
    }
    TTF_CloseFont(font);
}

void NumberedRect::init_number(unsigned int number, TTF_Font* font)
{
    bool newfont = false;
    if (font == nullptr)
        font = TTF_OpenFont(Definitions::DEFAULT_BLOCK_FONT_NAME.c_str(), Definitions::BLOCK_SIZE_X);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string((int) std::pow(2, number)).c_str(), Definitions::DEFAULT_BLOCK_FONT_COLOR);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(Window::get_single().get_renderer()), textSurface);
    SDL_FreeSurface(textSurface);
    NUMBERS[number] = texture;

    if (newfont)
        TTF_CloseFont(font);
}

void NumberedRect::draw() const
{
    Rect::draw();
    try { NUMBERS.at(m_number); }
    catch (const std::out_of_range&)
    {
        init_number(m_number);
    }
    SDL_RenderCopy(const_cast<SDL_Renderer*>(Window::get_single().get_renderer()), NUMBERS[m_number], NULL, &m_rect);
}
