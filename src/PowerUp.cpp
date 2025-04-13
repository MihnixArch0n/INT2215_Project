#include "PowerUp.hpp"

PowerUp::PowerUp(PowerUpDropType type)
{
    mType = type;
    if (type == PowerUpDropType::MULTI_BALL) mDuration = -1;
    else if (type == PowerUpDropType::FIRE_BALL) mDuration = 15 * 1000;
}

PowerUp::PowerUp(const PowerUp &other)
{
    mType = other.mType;
    mDuration = other.mDuration;
    mElapsedTime = other.mElapsedTime;
    mStatus = other.mStatus;
}


void PowerUp::update(int deltaTime)
{
    if (mStatus == PowerUpStatus::ACTIVATED)
    {
        mElapsedTime += deltaTime;
        if (mElapsedTime > mDuration) mStatus = PowerUpStatus::DEACTIVATED;
    }
}
