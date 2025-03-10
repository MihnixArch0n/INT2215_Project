#include <iostream>
#include <SDL_image.h>

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

void MyTexture::render(SDL_Renderer *renderer, const SDL_Rect* dst) const
{
    SDL_RenderCopy(renderer, mTexture, nullptr, dst);
}