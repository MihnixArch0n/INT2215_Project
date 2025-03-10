#include "RenderWindow.hpp"

bool RenderWindow::create(const char* title, int width, int height)
{
    mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr)
    {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED
            | SDL_RENDERER_PRESENTVSYNC);
        if (mRenderer == nullptr)
        {
            fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
            return false;
        }
    }
    return true;
}

SDL_Renderer* RenderWindow::getRenderer() const {return mRenderer;}

RenderWindow::~RenderWindow()
{
    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
}
