#include "game_objects/FireBall.hpp"

FireBall::FireBall() : mPowerUp(PowerUpDropType::FIRE_BALL)
{
    mSubType = BallType::FIRE;
}

FireBall::FireBall(const Ball &other) : Ball(other), mPowerUp(PowerUpDropType::FIRE_BALL)
{
    mSubType = BallType::FIRE;
}

void FireBall::update(int deltaTime, const Paddle &paddle)
{
    Ball::update(deltaTime, paddle);
    mPowerUp.update(deltaTime);
    if (mPowerUp.getStatus() == PowerUpStatus::DEACTIVATED)
    {
        mState = BallState::EXPIRED;
    }
}
