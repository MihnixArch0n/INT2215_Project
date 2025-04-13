#include "defs.hpp"
#include "game_objects/PowerUpDrop.hpp"
#include "game_objects/GameObject.hpp"


PowerUpDrop::PowerUpDrop()
{
    mWidth = WIDTH;
    mHeight = HEIGHT;
}

void PowerUpDrop::update(int deltaTime)
{
    if (mStatus == PowerUpDropStatus::ALIVE)
    {
        mPosY += mVel * deltaTime / 1000;
        if (mPosY > LEVEL_HEIGHT) mStatus = PowerUpDropStatus::DEAD;
    }
}

void PowerUpDrop::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::PADDLE) mStatus = PowerUpDropStatus::COLLECTED;
}

void PowerUpDrop::save(std::ofstream &saveFile) const
{
    GameObject::save(saveFile);
    saveFile << " " << static_cast<int>(std::get<PowerUpDropType>(mSubType));
    saveFile << " " << static_cast<int>(mStatus);
    saveFile << std::endl;
}

void PowerUpDrop::load(std::ifstream &loadFile)
{
    GameObject::load(loadFile);
    int tmp;
    loadFile >> tmp;
    mSubType = static_cast<PowerUpDropType>(tmp);
    loadFile >> tmp;
    mStatus = static_cast<PowerUpDropStatus>(tmp);
}

