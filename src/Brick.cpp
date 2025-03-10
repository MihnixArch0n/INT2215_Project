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

void Brick::update(const Ball& ball)
{
    if (isCollidedWithOther(ball)) alive = false;
}

