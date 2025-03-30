#include "defs.hpp"
#include "game_objects/Paddle.hpp"

Paddle::Paddle()
{
    mPosX = 300;
    mPosY = SCREEN_HEIGHT * 0.9;
    mWidth = M_PADDLE_WIDTH;
    mHeight = M_PADDLE_HEIGHT;
}


void Paddle::handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                mVel -= M_PADDLE_SPEED;
                break;
            case SDLK_RIGHT:
                mVel += M_PADDLE_SPEED;
                break;
            default: break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                mVel += M_PADDLE_SPEED;
            break;
            case SDLK_RIGHT:
                mVel -= M_PADDLE_SPEED;
            break;
            default: break;
        }
    }
}

void Paddle::update(int deltaTime)
{
    mPosX += mVel * deltaTime / 1000.0;
    if (mPosX < 0) mPosX = 0;
    if (mPosX + mWidth > SCREEN_WIDTH) mPosX = SCREEN_WIDTH - mWidth;
}

