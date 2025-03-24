#include "PowerUp.hpp"

PowerUp::PowerUp(PowerUpDropType type)
{
    mType = type;
    if (type == PowerUpDropType::MULTI_BALL) mDuration = -1;
    else if (type == PowerUpDropType::FIRE_BALL) mDuration = 900 * 1000;
}

void PowerUp::update()
{
    if (mStatus == PowerUpStatus::ACTIVATED)
    {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - mStartTime > mDuration) mStatus = PowerUpStatus::DEACTIVATED;
    }
}
