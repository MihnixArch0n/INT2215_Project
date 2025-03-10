#include "defs.hpp"
#include "Paddle.hpp"

Paddle::Paddle()
{
    mPosX = 300;
    mPosY = SCREEN_HEIGHT * 0.9;
    mWidth = 100;
    mHeight = 30;
}


void Paddle::handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                mVel -= M_SPEED;
                break;
            case SDLK_RIGHT:
                mVel += M_SPEED;
                break;
            default: break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                mVel += M_SPEED;
            break;
            case SDLK_RIGHT:
                mVel -= M_SPEED;
            break;
            default: break;
        }
    }
}

void Paddle::update()
{
    mPosX += mVel;
    if (mPosX < 0) mPosX = 0;
    if (mPosX + mWidth > SCREEN_WIDTH) mPosX = SCREEN_WIDTH - mWidth;
}

