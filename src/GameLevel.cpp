#include "GameLevel.hpp"

#include <iostream>

#include "managers/PowerUpManager.hpp"

GameLevel::GameLevel(const ResourceManager *manager) : mGameObjectManager(manager) {}


void GameLevel::init()
{
    mGameObjectManager.init(&mMediator);
    mPowerUpManager.init(&mMediator);
    mMediator.init(&mGameObjectManager, &mPowerUpManager);
}

void GameLevel::handleEvent(SDL_Event &event)
{
    mGameObjectManager.handleEvent(event);
}

void GameLevel::update(int deltaTime, GameState& gameState)
{
    if (!hasFinished())
    {
        mGameObjectManager.update(deltaTime);
        mPowerUpManager.update();

        if (mGameObjectManager.ballListEmpty())
        {
            --mLives;
            mGameObjectManager.resetBallList();
            mPowerUpManager.reset();
        }
        if (hasFinished() && gameState != GameState::QUIT) gameState = GameState::END;
    }
}

void GameLevel::render(SDL_Renderer *renderer) const
{
    mGameObjectManager.render(renderer);
}


void GameLevel::newLevel()
{
}

void GameLevel::loadLevel()
{
    // TODO: Load saved level from disk.
}

void GameLevel::saveLevel()
{
    // TODO: Save current level to disk.
}

