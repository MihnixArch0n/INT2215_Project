#include <cmath>
#include "defs.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

Ball::Ball()
{
    // mPosX = mPosY = 0;
    mPosX = 0, mPosY = SCREEN_HEIGHT * 0.9;
    mWidth = 32;
    mHeight = 32;
    mVelY = 1.5;
}

void Ball::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        mState = MOVING;
        mVelX = M_SPEED * cos(mPosX);
        mVelY = -sqrt(pow(M_SPEED, 2) - pow(mVelX, 2));
    }
}


void Ball::update(const Paddle& paddle, const std::vector<Brick>& bricksList)
{
    if (mState == START)
    {
        mPosX = paddle.getPosX() + (paddle.getWidth() - mWidth) / 2;
        mPosY = paddle.getPosY() - mHeight;
    }
    else if (mState == MOVING)
    {
        mPosX += mVelX;
        mPosY += mVelY;
        handleCollision(paddle, bricksList);
        if (mPosY > SCREEN_HEIGHT) mState = DEAD;
    }
}


void Ball::handleCollisionWithPaddle(const Paddle &paddle)
{
    if (isCollidedWithOther(paddle))
    {
        double checkPosY = mPosY - mVelY;
        double checkPosX = mPosX - mVelX;
        if (checkPosY + mHeight < paddle.getPosY())
        {
            mPosY = paddle.getPosY() - mHeight;
            mVelY = -mVelY;
        }
        else if (checkPosY > paddle.getPosY() + paddle.getHeight())
        {
            mPosY = paddle.getPosY() + paddle.getHeight();
            mVelY = -mVelY;
        }
        else if (checkPosX + mWidth < paddle.getPosX())
        {
            mPosX = paddle.getPosX() - mWidth;
            mVelX = -mVelX;
        }
        else
        {
            mPosX = paddle.getPosX() + paddle.getWidth();
            mVelX = -mVelX;
        }
    }
}


void Ball::handleCollisionWithBricks(const std::vector<Brick>& bricksList)
{
    for (const auto& brick : bricksList)
    {
        if (isCollidedWithOther(brick))
        {
            double checkPosY = mPosY - mVelY;
            double checkPosX = mPosX - mVelX;
            if (checkPosY + mHeight < brick.getPosY())
            {
                mPosY = brick.getPosY() - mHeight;
                mVelY = -mVelY;
            }
            else if (checkPosY > brick.getPosY() + brick.getHeight())
            {
                mPosY = brick.getPosY() + brick.getHeight();
                mVelY = -mVelY;
            }
            else if (checkPosX + mWidth < brick.getPosX())
            {
                mPosX = brick.getPosX() - mWidth;
                mVelX = -mVelX;
            }
            else
            {
                mPosX = brick.getPosX() + brick.getWidth();
                mVelX = -mVelX;
            }
        }
    }
}



void Ball::handleCollision(const Paddle& paddle, const std::vector<Brick>& bricksList)
{
    if (mPosX < 0)
    {
        mPosX = 0;
        mVelX = -mVelX;
    }
    if (mPosX + mWidth > SCREEN_WIDTH)
    {
        mPosX = SCREEN_WIDTH - mWidth;
        mVelX = -mVelX;
    }
    if (mPosY < 0)
    {
        mPosY = 0;
        mVelY = -mVelY;
    }
    handleCollisionWithPaddle(paddle);
    handleCollisionWithBricks(bricksList);
}

BallState Ball::getState() const {return mState;}
void Ball::setState(BallState state) {mState = state;}