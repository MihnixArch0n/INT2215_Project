#ifndef MYTEXTURE_HPP
#define MYTEXTURE_HPP


#include <SDL.h>

class MyTexture
{
public:
    ~MyTexture();

    void render(SDL_Renderer* renderer, const SDL_Rect* dst) const;
    bool loadFromFile(SDL_Renderer* renderer, const char *filePath);
private:
    int mTextureWidth = 0, mTextureHeight = 0;
    SDL_Texture *mTexture = nullptr;
};



#endif //MYTEXTURE_HPP
