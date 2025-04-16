#include "defs.hpp"
#include "my_utils.hpp"
#include "game_objects/PowerUpDrop.hpp"
#include "game_objects/GameObject.hpp"
#include "managers/AudioManager.hpp"


PowerUpDrop::PowerUpDrop()
{
    mWidth = WIDTH;
    mHeight = HEIGHT;
}

void PowerUpDrop::init(ResourceManager &manager)
{
    auto type = ObjectType::POWER_UP_DROP;
    std::string resPath = "assets/img/power_ups";

    manager.addTexture(type, PowerUpType::FIRE_BALL, resPath + "/p_FireBall.png");
    manager.addTexture(type, PowerUpType::MULTI_BALL, resPath + "/p_MultiBall.png");
}


void PowerUpDrop::update(int deltaTime)
{
    if (mStatus == PowerUpDropStatus::ALIVE)
    {
        mPosY += mVel * my_utils::to_seconds(deltaTime);
        if (mPosY > LEVEL_HEIGHT) mStatus = PowerUpDropStatus::DEAD;
    }
}

void PowerUpDrop::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::PADDLE)
    {
        mStatus = PowerUpDropStatus::COLLECTED;
        AudioManager::getInstance().getSound(SoundType::COLLECT)->play();
    }
}

void PowerUpDrop::save(std::ofstream &saveFile) const
{
    GameObject::save(saveFile);
    saveFile << " " << static_cast<int>(std::get<PowerUpType>(mSubType));
    saveFile << " " << static_cast<int>(mStatus);
    saveFile << std::endl;
}

void PowerUpDrop::load(std::ifstream &loadFile)
{
    GameObject::load(loadFile);
    int tmp;
    loadFile >> tmp;
    mSubType = static_cast<PowerUpType>(tmp);
    loadFile >> tmp;
    mStatus = static_cast<PowerUpDropStatus>(tmp);
}

