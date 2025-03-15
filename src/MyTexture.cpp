#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "MyTexture.hpp"


MyTexture::~MyTexture()
{
    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}

bool MyTexture::loadFromFile(SDL_Renderer *renderer, const char *filePath)
{
    mTexture = IMG_LoadTexture(renderer, filePath);
    if (mTexture == nullptr)
    {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_QueryTexture(mTexture, nullptr, nullptr,
        &mTextureWidth, &mTextureHeight);
    return true;
}

bool MyTexture::loadFromRenderedText(const char *text, const MyFont &font, SDL_Renderer* renderer)
{
    SDL_Color color = {0, 0, 0};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font.getFont(), text, color);
    if (textSurface == nullptr)
    {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (mTexture == nullptr)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return false;
    }
    mTextureWidth = textSurface->w;
    mTextureHeight = textSurface->h;

    return true;
}


void MyTexture::render(SDL_Renderer *renderer, const SDL_Rect* dst) const
{
    SDL_RenderCopy(renderer, mTexture, nullptr, dst);
}

void MyTexture::render(int x, int y, SDL_Renderer *renderer) const
{
    SDL_Rect dst = {x, y, mTextureWidth, mTextureHeight};
    SDL_RenderCopy(renderer, mTexture, nullptr, &dst);
}