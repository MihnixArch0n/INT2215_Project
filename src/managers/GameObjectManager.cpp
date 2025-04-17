#include "managers/GameObjectManager.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "my_utils.hpp"
#include "managers/CollisionManager.hpp"


constexpr int BALL_SEP = 20;


GameObjectManager::GameObjectManager(ResourceManager& manager) : rResourceManager(manager)
{
}

void GameObjectManager::init()
{
    mPaddle.setTexture(rResourceManager);

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

    mPowerUpDropList.erase(
        std::remove_if(
            mPowerUpDropList.begin(),mPowerUpDropList.end(),
            [](const PowerUpDrop& p) {
                return p.getStatus() != PowerUpDropStatus::ALIVE;
            }),
        mPowerUpDropList.end());

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

    }

    for (auto &powerUpDrop : mPowerUpDropList)
    {
        powerUpDrop.update(deltaTime);
        CollisionManager::handleCollision(mPaddle, powerUpDrop, deltaTime);
    }

    mBallList.erase(
        std::remove_if(mBallList.begin(), mBallList.end(),
            [](const std::unique_ptr<Ball>& ball) {
                return ball->getState() == BallState::DEAD;
            }),
        mBallList.end());

    for (int i = 0; i < BRICK_ROW; ++i)
    {
        for (int j = mBricksList[i].size()-1; j >= 0; --j)
        {
            if (!mBricksList[i][j].isAlive())
            {
                auto brickType = std::get<BrickType>(mBricksList[i][j].getSubType());
                if (mBricksList[i][j].hasDrop())
                {
                    auto powerUpType = static_cast<PowerUpType>(
                        my_utils::uniform_random(
                            0,
                            static_cast<int>(PowerUpType::TOTAL) - 1
                        )
                    );
                    spawnDrop(powerUpType, mBricksList[i][j].getPosX(),
                        mBricksList[i][j].getPosY());
                }
                mBricksList[i].erase(mBricksList[i].begin() + j);
            }
        }
    }

}

void GameObjectManager::render(SDL_Renderer* renderer) const
{
    mPaddle.render(renderer);

    for (const auto &brickRow : mBricksList)
    {
        for (const auto &brick : brickRow) brick.render(renderer);
    }

    for (const auto &ball : mBallList) ball->render(renderer);

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

void GameObjectManager::changeBall(const std::unique_ptr<Ball>& ball, BallType ballType) const
{
    ball->setSubType(ballType);
    ball->setTexture(rResourceManager);
}

PowerUpType GameObjectManager::getCollectedPowerUp() const
{
    for (const auto &powerUpDrop : mPowerUpDropList)
    {
        if (powerUpDrop.getStatus() == PowerUpDropStatus::COLLECTED)
            return std::get<PowerUpType>(powerUpDrop.getSubType());
    }
    return PowerUpType::TOTAL;
}

void GameObjectManager::applyPowerUp(PowerUpType type)
{
    if (type == PowerUpType::MULTI_BALL)
    {
        size_t n = mBallList.size();
        for (size_t i = 0; i < n; ++i)
        {
            double x = mBallList[i]->getPosX();
            double y = mBallList[i]->getPosY();

            addBall(*mBallList[i], x - BALL_SEP, y);
            addBall(*mBallList[i], x + BALL_SEP, y);
        }
    }
    else if (type == PowerUpType::FIRE_BALL)
    {
        for (auto &ball : mBallList) changeBall(ball, BallType::FIRE);
    }
}

void GameObjectManager::removePowerUp(PowerUpType type)
{
    if (type == PowerUpType::FIRE_BALL)
        for (auto &ball : mBallList) changeBall(ball, BallType::NORMAL);
}


void GameObjectManager::spawnDrop(PowerUpType type, double x, double y)
{
    mPowerUpDropList.emplace_back();
    mPowerUpDropList.back().setSubType(type);
    mPowerUpDropList.back().setTexture(rResourceManager);
    mPowerUpDropList.back().setPosX(x);
    mPowerUpDropList.back().setPosY(y);
}

void GameObjectManager::save() const
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
        mPaddle.setTexture(rResourceManager);

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
            powerUpDrop.setTexture(rResourceManager);
        }
        powerUpFile.close();
    }
}

bool GameObjectManager::brickListEmpty() const
{
    for (const auto& brickRow : mBricksList)
    {
        if (!brickRow.empty()) return false;
    }
    return true;
}

