#include "ResourceManager.hpp"

#include <iostream>

bool ResourceManager::loadResource(SDL_Renderer* renderer)
{
    bool success = true;
    if (!mPaddleTexture.loadFromFile(renderer, "assets/img/paddles/Paddle_1.png"))
    {
        std::cerr << "Failed to load paddle texture" << std::endl;
        success = false;
    }
    if (!mBallTexture.loadFromFile(renderer, "assets/img/balls/Ball_1.png"))
    {
        std::cerr << "Failed to load ball texture" << std::endl;
        success = false;
    }
    if (!mBrickTexture.loadFromFile(renderer, "assets/img/bricks/Brick_1.png"))
    {
        std::cerr << "Failed to load brick texture" << std::endl;
        success = false;
    }
    if (mFont.loadFont("res/fonts/GohuFont14NerdFontMono-Regular.ttf", 42))
    {
        if (!mWonTexture.loadFromRenderedText("You won", mFont, renderer))
        {
            std::cerr << "Failed to load won texture" << std::endl;
            success = false;
        }
        if (!mLostTexture.loadFromRenderedText("You lost", mFont, renderer))
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
    if (!mSound.loadSound("assets/audio/sound/hit02.mp3.flac"))
    {
        std::cerr << "Failed to load sound" << std::endl;
        success = false;
    }
    if (!mMusic.loadMusic("assets/audio/music/best-game-console-301284.mp3"))
    {
        std::cerr << "Failed to load music" << std::endl;
        success = false;
    }
    return success;
}
