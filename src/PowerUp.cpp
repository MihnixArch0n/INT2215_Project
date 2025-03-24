#include "PowerUp.hpp"


void PowerUp::activate()
{
    mStatus = PowerUpStatus::ACTIVATED;
    mStartTime = SDL_GetTicks();
}

void PowerUp::deactivate()
{
    mStatus = PowerUpStatus::DEACTIVATED;
}

void PowerUp::update()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - mStartTime > mDuration) deactivate();
}
