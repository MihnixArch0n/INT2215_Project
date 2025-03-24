#include "PowerUpDrop.hpp"
#include "GameObject.hpp"
#include "defs.hpp"


PowerUpDrop::PowerUpDrop(ObjectSubType type)
{
    mWidth = WIDTH;
    mHeight = HEIGHT;
    mSubType = type;
}


void PowerUpDrop::update(int deltaTime)
{
    mPosY += mVel * deltaTime / 1000;
    if (mPosY > SCREEN_WIDTH) mIsAlive = false;
}

void PowerUpDrop::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::PADDLE) mIsAlive = false;
}

