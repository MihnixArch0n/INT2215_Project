#include "managers/GameObjectManager.hpp"

#include <filesystem>
#include <fstream>

#include "managers/CollisionManager.hpp"


GameObjectManager::GameObjectManager(ResourceManager& manager) : rResourceManager(manager)
{
}

void GameObjectManager::init()
{
    mBallList.push_back(std::make_unique<Ball>());
    mBricksList.resize(5);
    mPaddle.setObjectTexture(rResourceManager);
    for (auto &ball : mBallList)
    {
        ball->setObjectTexture(rResourceManager);
    }
    for (int i = 0; i < 5; i++)
    {
        mBricksList[i].setObjectTexture(rResourceManager);
    }

}

void GameObjectManager::handleEvent(const SDL_Event &event)
{
    mPaddle.handleEvent(event);
    for (auto &ball : mBallList) ball->handleEvent(event);
}

void GameObjectManager::update(int deltaTime)
{
    mPaddle.update(deltaTime);
    for (auto &ball : mBallList) ball->update(deltaTime, mPaddle);
    int ballsLeft = mBallList.size();
    for (int i = ballsLeft-1; i >= 0; --i)
    {
        CollisionManager::handleCollision(*mBallList[i], mPaddle, deltaTime);
        int bricksLeft = mBricksList.size();
        for (int j = bricksLeft-1; j >= 0; --j)
        {
            CollisionManager::handleCollision(*mBallList[i], mBricksList[j], deltaTime);
            if (!mBricksList[j].isAlive())
            {
                spawnDrop(PowerUpDropType::FIRE_BALL,
                    mBricksList[j].getPosX(), mBricksList[j].getPosY());
                mBricksList.erase(mBricksList.begin() + j);
            }
        }
        if (mBallList[i]->getState() == BallState::EXPIRED)
        {
            changeBall(mBallList[i], BallType::NORMAL);
        }
        if (mBallList[i]->getState() == BallState::DEAD) mBallList.erase(mBallList.begin() + i);
    }
    for (auto &powerUpDrop : mPowerUpDropList)
    {
        powerUpDrop.update(deltaTime);
        CollisionManager::handleCollision(mPaddle, powerUpDrop, deltaTime);

        if (powerUpDrop.getStatus() == PowerUpDropStatus::COLLECTED)
        {
            auto powerUpType = std::get<PowerUpDropType>(powerUpDrop.getSubType());
            int ballNum = mBallList.size();
            if (powerUpType == PowerUpDropType::MULTI_BALL)
            {
                for (int i = 0; i < ballNum; ++i)
                {
                    const auto& cBall = *mBallList[i];
                    addBall(cBall, cBall.getPosX() - 50, cBall.getPosY());
                    addBall(cBall, cBall.getPosX() + 50, cBall.getPosY());
                }
            }
            else if (powerUpType == PowerUpDropType::FIRE_BALL)
            {
                for (int i = 0; i < ballNum; ++i) changeBall(mBallList[i], BallType::FIRE);
            }
        }
    }
    for (int i = mPowerUpDropList.size()-1; i >= 0; --i)
    {
        if (mPowerUpDropList[i].getStatus() != PowerUpDropStatus::ALIVE)
            mPowerUpDropList.erase(mPowerUpDropList.begin() + i);
    }
}

void GameObjectManager::render(SDL_Renderer* renderer) const
{
    mPaddle.render(renderer);
    for (const auto &ball : mBallList) ball->render(renderer);
    for (const auto &brick : mBricksList) brick.render(renderer);
    for (const auto &powerUpDrop : mPowerUpDropList)
    {
        SDL_GetTicks();
        powerUpDrop.render(renderer);
    }
}

void GameObjectManager::resetBallList()
{
    mBallList.clear();
    mBallList.push_back(std::make_unique<Ball>());
    mBallList[0]->setObjectTexture(rResourceManager);
    mBallList[0]->setState(BallState::START);
}

void GameObjectManager::addBall(const Ball& ball, double x, double y)
{
    mBallList.push_back(std::make_unique<Ball>(Ball(ball, x, y)));
}

void GameObjectManager::changeBall(std::unique_ptr<Ball>& ball, BallType ballType)
{
    ball = std::make_unique<Ball>(*ball, ballType);
    ball->setObjectTexture(rResourceManager);
}


void GameObjectManager::spawnDrop(PowerUpDropType type, double x, double y)
{
    mPowerUpDropList.emplace_back();
    mPowerUpDropList.back().setSubType(type);
    mPowerUpDropList.back().setObjectTexture(rResourceManager);
    mPowerUpDropList.back().setPosX(x);
    mPowerUpDropList.back().setPosY(y);
}

void GameObjectManager::save()
{
    std::filesystem::create_directory("save/objects");

    std::ofstream paddleFile("save/objects/paddle.txt");
    mPaddle.save(paddleFile);
    paddleFile.close();

    std::ofstream ballFile("save/objects/ball.txt");
    ballFile << mBallList.size() << std::endl;
    for (const auto &ball : mBallList) ball->save(ballFile);
    ballFile.close();

    std::ofstream brickFile("save/objects/bricks.txt");
    brickFile << mBricksList.size() << std::endl;
    for (const auto &brick : mBricksList) brick.save(brickFile);
    brickFile.close();

    std::ofstream powerUpFile("save/objects/powerUp.txt");
    powerUpFile << mPowerUpDropList.size() << std::endl;
    for (const auto &powerUpDrop : mPowerUpDropList) powerUpDrop.save(powerUpFile);
    powerUpFile.close();
}

void GameObjectManager::load()
{
    if (std::filesystem::exists("save/objects"))
    {
        std::ifstream paddleFile("save/objects/paddle.txt");
        mPaddle.load(paddleFile);
        paddleFile.close();
        mPaddle.setObjectTexture(rResourceManager);

        int n;

        std::ifstream ballFile("save/objects/ball.txt");
        ballFile >> n;
        mBallList.resize(n);
        for (auto &ball : mBallList)
        {
            ball->load(ballFile);
            ball->setObjectTexture(rResourceManager);
        }
        ballFile.close();

        std::ifstream brickFile("save/objects/bricks.txt");
        brickFile >> n;
        mBricksList.resize(n);
        for (auto &brick : mBricksList)
        {
            brick.load(brickFile);
            brick.setObjectTexture(rResourceManager);
        }
        brickFile.close();

        std::ifstream powerUpFile("save/objects/powerUp.txt");
        powerUpFile >> n;
        mPowerUpDropList.resize(n);
        for (auto &powerUpDrop : mPowerUpDropList)
        {
            powerUpDrop.load(powerUpFile);
            powerUpDrop.setObjectTexture(rResourceManager);
        }
        powerUpFile.close();
    }
}
