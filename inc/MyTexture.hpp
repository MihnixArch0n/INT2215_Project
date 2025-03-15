#ifndef MYTEXTURE_HPP
#define MYTEXTURE_HPP


#include <SDL.h>

#include "MyFont.hpp"

class MyTexture
{
public:
    ~MyTexture();

    void render(SDL_Renderer* renderer, const SDL_Rect* dst) const;
    void render(int x, int y, SDL_Renderer* renderer) const;
    bool loadFromFile(SDL_Renderer* renderer, const char *filePath);
    bool loadFromRenderedText(const char* text, const MyFont& font, SDL_Renderer* renderer);
private:
    int mTextureWidth = 0, mTextureHeight = 0;
    SDL_Texture *mTexture = nullptr;
};



#endif //MYTEXTURE_HPP
