#include "defs.hpp"
#include "game_objects/Brick.hpp"
#include "game_objects/Ball.hpp"


Brick::Brick()
{
    mPosX = rand() % (LEVEL_WIDTH - BRICK_WIDTH);
    mPosY = rand() % (LEVEL_HEIGHT / 2 - BRICK_HEIGHT);
    mWidth = BRICK_WIDTH;
    mHeight = BRICK_HEIGHT;

    mSubType = BrickType::NORMAL;
}

bool Brick::isAlive() const {return alive;}

void Brick::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::BALL) alive = false;
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
