#include "defs.hpp"
#include "game_objects/PowerUpDrop.hpp"
#include "game_objects/GameObject.hpp"


PowerUpDrop::PowerUpDrop(ObjectSubType type)
{
    mWidth = WIDTH;
    mHeight = HEIGHT;
    mSubType = type;
}

void PowerUpDrop::update(int deltaTime)
{
    if (mStatus == PowerUpDropStatus::ALIVE)
    {
        mPosY += mVel * deltaTime / 1000;
        if (mPosY > SCREEN_WIDTH) mStatus = PowerUpDropStatus::DEAD;
    }
}

void PowerUpDrop::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::PADDLE) mStatus = PowerUpDropStatus::COLLECTED;
}

