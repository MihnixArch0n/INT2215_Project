#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include "Game.hpp"


bool initAll_SDL();
void closeAll_SDL();


int main(int argc, char *argv[])
{
    if (initAll_SDL())
    {
        Game myGame;
        myGame.loop();
    }
    closeAll_SDL();
    return 0;
}


bool initAll_SDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (IMG_Init(imgFlags) != imgFlags)
    {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        return false;
    }
    if (TTF_Init() < 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void closeAll_SDL()
{
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}