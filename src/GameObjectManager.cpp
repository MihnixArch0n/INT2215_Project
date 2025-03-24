#include "GameObjectManager.hpp"
#include "CollisionManager.hpp"
#include "Mediator.hpp"

GameObjectManager::GameObjectManager(const ResourceManager* manager) : rResourceManager(*manager)
{
    mBallList.resize(1);
    mBricksList.resize(5);
}

void GameObjectManager::init(Mediator* mediator)
{
    pMediator = mediator;
    mPaddle.setObjectTexture(rResourceManager.getTexture(ObjectType::PADDLE,
        PaddleType::NORMAL));
    for (auto &ball : mBallList)
    {
        ball.setObjectTexture(rResourceManager.getTexture(ObjectType::BALL,
            BallType::NORMAL));
    }
    for (int i = 0; i < 5; i++)
    {
        mBricksList[i].setObjectTexture(rResourceManager.getTexture(ObjectType::BRICK,
            BrickType::NORMAL));
    }

}

void GameObjectManager::handleEvent(const SDL_Event &event)
{
    mPaddle.handleEvent(event);
    for (auto &ball : mBallList) ball.handleEvent(event);
}

void GameObjectManager::update(int deltaTime)
{
    mPaddle.update(deltaTime);
    for (auto &ball : mBallList) ball.update(deltaTime, mPaddle);
    int ballsLeft = mBallList.size();
    for (int i = ballsLeft-1; i >= 0; --i)
    {
        CollisionManager::handleCollision(mBallList[i], mPaddle, deltaTime);
        int bricksLeft = mBricksList.size();
        for (int j = bricksLeft-1; j >= 0; --j)
        {
            CollisionManager::handleCollision(mBallList[i], mBricksList[j], deltaTime);
            if (!mBricksList[j].isAlive())
            {
                spawnDrop(PowerUpDropType::FIRE_BALL,
                    mBricksList[j].getPosX(), mBricksList[j].getPosY());
                mBricksList.erase(mBricksList.begin() + j);
            }
        }
        if (mBallList[i].getState() == BallState::DEAD) mBallList.erase(mBallList.begin() + i);
    }
    for (auto &powerUpDrop : mPowerUpDropList)
    {
        powerUpDrop.update(deltaTime);
        CollisionManager::handleCollision(mPaddle, powerUpDrop, deltaTime);
        if (CollisionManager::checkCollision(mPaddle, powerUpDrop))
        {
            auto powerUpType = std::get<PowerUpDropType>(powerUpDrop.getSubType());
            pMediator->notify(powerUpType, "collect");
        }
    }
    for (int i = mPowerUpDropList.size()-1; i >= 0; --i)
    {
        if (!mPowerUpDropList[i].isAlive()) mPowerUpDropList.erase(mPowerUpDropList.begin() + i);
    }
}

void GameObjectManager::render(SDL_Renderer* renderer) const
{
    mPaddle.render(renderer);
    for (const auto &ball : mBallList) ball.render(renderer);
    for (const auto &brick : mBricksList) brick.render(renderer);
    for (const auto &powerUpDrop : mPowerUpDropList)
    {
        SDL_GetTicks();
        powerUpDrop.render(renderer);
    }
}

void GameObjectManager::resetBallList()
{
    mBallList.emplace_back();
    mBallList[0].setObjectTexture(rResourceManager.getTexture(ObjectType::BALL,
        BallType::NORMAL));
    mBallList[0].setState(BallState::START);
}

void GameObjectManager::addBall(const Ball& ball, double x, double y)
{
    mBallList.emplace_back(ball, x, y);
}

void GameObjectManager::makeFireBall(int index)
{
    mBallList[index].setObjectTexture(rResourceManager.getTexture(ObjectType::BALL,
        BallType::FIRE));
    mBallList[index].setSubType(BallType::FIRE);
}

void GameObjectManager::makeNormalBall(int index)
{
    mBallList[index].setObjectTexture(rResourceManager.getTexture(ObjectType::BALL,
        BallType::NORMAL));
    mBallList[index].setSubType(BallType::NORMAL);
}


void GameObjectManager::spawnDrop(PowerUpDropType type, double x, double y)
{
    mPowerUpDropList.emplace_back(type);
    mPowerUpDropList.back().setObjectTexture(rResourceManager.getTexture(
        ObjectType::POWER_UP_DROP, type));
    mPowerUpDropList.back().setPosX(x);
    mPowerUpDropList.back().setPosY(y);
}