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
    auto type = ObjectType::BRICK;
    std::string resPath = "assets/img/bricks";
    manager.addTexture(type, BrickType::EASY, resPath + "/EasyBrick.png");
    manager.addTexture(type, BrickType::MEDIUM, resPath + "/MediumBrick.png");
    manager.addTexture(type, BrickType::HARD, resPath + "/HardBrick.png");
}

void Brick::update(int deltaTime, const ResourceManager &manager)
{
    timeSinceLastCooldown += deltaTime;
    setTexture(manager);
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
    saveFile << " " << static_cast<int>(std::get<BrickType>(mSubType));
    saveFile << " " << lives;
    saveFile << " " << timeSinceLastCooldown;
    saveFile << std::endl;
}

void Brick::load(std::ifstream &loadFile)
{
    GameObject::load(loadFile);
    int tmp;
    loadFile >> tmp;
    mSubType = static_cast<BrickType>(tmp);
    loadFile >> lives;
    loadFile >> timeSinceLastCooldown;
}
