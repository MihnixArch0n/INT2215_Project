#include "managers/GameObjectManager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "managers/CollisionManager.hpp"


GameObjectManager::GameObjectManager(ResourceManager& manager) : rResourceManager(manager)
{
}

void GameObjectManager::init()
{
    mPaddle.setObjectTexture(rResourceManager);

    mBallList.push_back(std::make_unique<Ball>());

    for (auto &ball : mBallList) ball->setTexture(rResourceManager);

    for (int i = 0; i < BRICK_ROW; ++i)
    {
        mBricksList.emplace_back();
        for (int j = 0; j < BRICK_COLUMN; ++j)
        {
            mBricksList[i].emplace_back();
            mBricksList[i][j].setPosY(i * Brick::BRICK_HEIGHT);
            mBricksList[i][j].setPosX(j * Brick::BRICK_WIDTH);
            mBricksList[i][j].setTexture(rResourceManager);
        }
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

    for (auto &brickRow : mBricksList)
    {
        for (auto &brick : brickRow) brick.update(deltaTime, rResourceManager);
    }

    for (auto &ball : mBallList)
    {
        ball->update(deltaTime, mPaddle);

        CollisionManager::handleCollision(*ball, mPaddle, deltaTime);

        for (auto &brickRow : mBricksList)
        {
            for (auto &brick : brickRow)
                CollisionManager::handleCollision(*ball, brick, deltaTime);
        }

        if (ball->getState() == BallState::EXPIRED) changeBall(ball, BallType::NORMAL);
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

    for (int i = mBallList.size()-1; i >= 0; --i)
    {
        if (mBallList[i]->getState() == BallState::DEAD)
            mBallList.erase(mBallList.begin() + i);
    }

    for (int i = 0; i < BRICK_ROW; ++i)
    {
        for (int j = mBricksList[i].size()-1; j >= 0; --j)
        {
            if (!mBricksList[i][j].isAlive())
            {
                spawnDrop(PowerUpDropType::FIRE_BALL, mBricksList[i][j].getPosX(),
                    mBricksList[i][j].getPosY());
                mBricksList[i].erase(mBricksList[i].begin() + j);
            }
        }
    }
}

void GameObjectManager::render(SDL_Renderer* renderer) const
{
    mPaddle.render(renderer);

    for (const auto &ball : mBallList) ball->render(renderer);

    for (const auto &brickRow : mBricksList)
    {
        for (const auto &brick : brickRow) brick.render(renderer);
    }

    for (const auto &powerUpDrop : mPowerUpDropList) powerUpDrop.render(renderer);
}

void GameObjectManager::resetBallList()
{
    mBallList.clear();
    mBallList.push_back(std::make_unique<Ball>());
    mBallList[0]->setTexture(rResourceManager);
    mBallList[0]->setState(BallState::START);
}

void GameObjectManager::addBall(const Ball& ball, double x, double y)
{
    mBallList.push_back(std::make_unique<Ball>(Ball(ball, x, y)));
}

void GameObjectManager::changeBall(std::unique_ptr<Ball>& ball, BallType ballType)
{
    ball = std::make_unique<Ball>(*ball, ballType);
    ball->setTexture(rResourceManager);
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
    for (const auto &brickRow : mBricksList)
    {
        brickFile << brickRow.size() << std::endl;
        for (const auto &brick : brickRow) brick.save(brickFile);
    }
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
            ball->setTexture(rResourceManager);
        }
        ballFile.close();

        std::ifstream brickFile("save/objects/bricks.txt");
        mBricksList.resize(BRICK_ROW);
        for (auto &brickRow : mBricksList)
        {
            brickFile >> n;
            brickRow.resize(n);
            for (auto &brick : brickRow)
            {
                brick.load(brickFile);
                brick.setTexture(rResourceManager);
            }
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
