#include <cmath>
#include "defs.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

/**
 * Linear mapping to radian angle based on hit position.
*/
constexpr double HIT_POS_START = -(Paddle::M_PADDLE_WIDTH - Ball::M_BALL_WIDTH) / 2.0;
constexpr double HIT_POS_END = (Paddle::M_PADDLE_WIDTH - Ball::M_BALL_WIDTH) / 2.0;
constexpr double RAD_ANGLE_START = 3 * M_PI_4;
constexpr double RAD_ANGLE_END = M_PI_4;


Ball::Ball()
{
    // mPosX = mPosY = 0;
    mPosX = 0;
    mPosY = SCREEN_HEIGHT * 0.9;
    mWidth = M_BALL_WIDTH;
    mHeight = M_BALL_HEIGHT;
    mVelY = 1.5;
}

void Ball::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        mState = MOVING;
        mVelX = 0;
        mVelY = -M_BALL_SPEED;
    }
}


void Ball::update(const Paddle& paddle, const std::vector<Brick>& bricksList)
{
    if (mState == START)
    {
        mPosX = paddle.getPosX() + (paddle.getWidth() - mWidth) / 2.0;
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

        double ballCenterX = mPosX + mWidth / 2.0;
        double paddleCenterX = paddle.getPosX() + paddle.getWidth() / 2.0;

        if (checkPosY + mHeight < paddle.getPosY())
        {
            mPosY = paddle.getPosY() - mHeight;
            double angle = (ballCenterX - paddleCenterX - HIT_POS_START)
                / (HIT_POS_END - HIT_POS_START);
            angle = angle * (RAD_ANGLE_END - RAD_ANGLE_START) + RAD_ANGLE_START;
            mVelX = M_BALL_SPEED * cos(angle);
            mVelY = -M_BALL_SPEED * sin(angle);
        }
        else if (checkPosY > paddle.getPosY() + paddle.getHeight())
        {
            mPosY = paddle.getPosY() + paddle.getHeight();
            double angle = (ballCenterX - paddleCenterX - HIT_POS_START)
                / (HIT_POS_END - HIT_POS_START);
            angle = angle * (RAD_ANGLE_END - RAD_ANGLE_START) + RAD_ANGLE_START;
            mVelX = M_BALL_SPEED * cos(angle);
            mVelY = M_BALL_SPEED * sin(angle);
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