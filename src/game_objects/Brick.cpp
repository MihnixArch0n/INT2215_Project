#include "defs.hpp"
#include "game_objects/Brick.hpp"

#include <iostream>

#include "game_objects/Ball.hpp"


Brick::Brick()
{
    mPosX = rand() % (LEVEL_WIDTH - BRICK_WIDTH);
    mPosY = rand() % (LEVEL_HEIGHT / 2 - BRICK_HEIGHT);
    mWidth = BRICK_WIDTH;
    mHeight = BRICK_HEIGHT;

    int tmp = rand() % static_cast<int>(BrickType::TOTAL);
    mSubType = static_cast<BrickType>(tmp);
    lives = tmp + 1;
    if (lives <= 0) std::cerr << "brick " << this << " live not set properly";
}

Brick::Brick(int x, int y, BrickType type) : Brick()
{
    mPosX = x;
    mPosY = y;

    mSubType = type;
    lives = static_cast<int>(type);
}


void Brick::init(ResourceManager &manager)
{
    std::string resPath = "assets/img/bricks";
    if (std::get<BrickType>(mSubType) == BrickType::EASY) resPath += "/EasyBrick.png";
    else if (std::get<BrickType>(mSubType) == BrickType::MEDIUM) resPath += "/MediumBrick.png";
    else if (std::get<BrickType>(mSubType) == BrickType::HARD) resPath += "/HardBrick.png";

    manager.addTexture(getType(), mSubType, resPath);
    setObjectTexture(manager);
}

void Brick::setObjectTexture(const ResourceManager &manager)
{
    mObjectTexture = manager.getObjectTexture(getType(), mSubType);
}

void Brick::update(int deltaTime, const ResourceManager &manager)
{
    timeSinceLastCooldown += deltaTime;
    setObjectTexture(manager);
}


void Brick::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::BALL)
    {
        if (timeSinceLastCooldown > COLLISION_COOLDOWN)
        {
            --lives;
            mSubType = static_cast<BrickType>(lives - 1);
            timeSinceLastCooldown = 0;
        }
    }
}

void Brick::save(std::ofstream &saveFile) const
{
    GameObject::save(saveFile);
    saveFile << " " << alive;
    saveFile << std::endl;
}

void Brick::load(std::ifstream &loadFile)
{
    GameObject::load(loadFile);
    loadFile >> alive;
}
