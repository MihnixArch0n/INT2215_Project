#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "MyTexture.hpp"
#include "MyFont.hpp"
#include "defs.hpp"
#include "Game.hpp"


bool initAll_SDL();
void closeAll_SDL();

RenderWindow gWindow;
MyTexture gPaddleTexture;
MyTexture gBallTexture;
MyTexture gBrickTexture;
MyFont gFont;
MyTexture wonTexture;
MyTexture lostTexture;

bool loadMedia(const Game& myGame);

int main(int argc, char *argv[])
{
    if (initAll_SDL())
    {
        gWindow.create(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
        Game myGame(&gWindow);
        if (!loadMedia(myGame))
        {
            std::cerr << "Failed to load media" << std::endl;
        }
        else
        {
            myGame.init(&gPaddleTexture, &gBallTexture, &gBrickTexture);
            SDL_SetRenderDrawColor(myGame.getRenderer(), 255, 255, 255, 255);
            SDL_RenderClear(myGame.getRenderer());
            do
            {
                myGame.handleEvent();
                myGame.update();
                myGame.render();
            }
            while (!myGame.hasFinished());
            SDL_RenderClear(gWindow.getRenderer());
            if (myGame.hasWon()) wonTexture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, myGame.getRenderer());
            if (myGame.hasLost()) lostTexture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, myGame.getRenderer());
            SDL_RenderPresent(gWindow.getRenderer());
            SDL_Delay(1000);
        }
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
    return true;
}

bool loadMedia(const Game& myGame)
{
    SDL_Renderer* renderer = gWindow.getRenderer();
    bool success = true;
    if (!gPaddleTexture.loadFromFile(renderer, "assets/paddles/Paddle_1.png"))
    {
        std::cerr << "Failed to load paddle texture" << std::endl;
        success = false;
    }
    if (!gBallTexture.loadFromFile(renderer, "assets/balls/Ball_1.png"))
    {
        std::cerr << "Failed to load ball texture" << std::endl;
        success = false;
    }
    if (!gBrickTexture.loadFromFile(renderer, "assets/bricks/Brick_1.png"))
    {
        std::cerr << "Failed to load brick texture" << std::endl;
        success = false;
    }
    if (gFont.loadFont("res/fonts/GohuFont14NerdFontMono-Regular.ttf", 14))
    {
        if (!wonTexture.loadFromRenderedText("You won", gFont, renderer))
        {
            std::cerr << "Failed to load won texture" << std::endl;
            success = false;
        }
        if (!lostTexture.loadFromRenderedText("You lost", gFont, renderer))
        {
            std::cerr << "Failed to load lost texture" << std::endl;
            success = false;
        }
    }
    else
    {
        std::cerr << "Failed to load font " << std::endl;
        success = false;
    }
    return success;
}


void closeAll_SDL()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}