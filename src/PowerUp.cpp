#include "PowerUp.hpp"
#include "my_utils.hpp"


PowerUp::PowerUp(PowerUpType type)
{
    mType = type;
    if (type == PowerUpType::MULTI_BALL) mDuration = -1;
    else if (type == PowerUpType::FIRE_BALL) mDuration = 15;
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
        mElapsedTime += my_utils::to_seconds(deltaTime);
        if (mElapsedTime > mDuration) mStatus = PowerUpStatus::DEACTIVATED;
    }
}
