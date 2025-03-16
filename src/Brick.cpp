#include "defs.hpp"
#include "Brick.hpp"
#include "Ball.hpp"


Brick::Brick()
{
    mPosX = rand() % (SCREEN_WIDTH - BRICK_WIDTH);
    mPosY = rand() % (SCREEN_HEIGHT / 2 - BRICK_HEIGHT);
    mWidth = BRICK_WIDTH;
    mHeight = BRICK_HEIGHT;
}

bool Brick::isAlive() const {return alive;}

void Brick::onCollision(GameObject &other, int deltaTime)
{
    if (other.getType() == ObjectType::BALL) alive = false;
}
