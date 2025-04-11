#include "GameLevel.hpp"

#include <filesystem>
#include <fstream>


GameLevel::GameLevel(ResourceManager& manager) : rResourceManager(manager)
{
}

void GameLevel::init()
{
    mGameObjectManager = std::make_unique<GameObjectManager>(rResourceManager);
    mGameObjectManager->init();
    mLives = 3;
}

void GameLevel::handleEvent(SDL_Event &event)
{
    mGameObjectManager->handleEvent(event);
}

void GameLevel::update(int deltaTime, GameState& gameState)
{
    if (!hasFinished())
    {
        mGameObjectManager->update(deltaTime);

        if (mGameObjectManager->ballListEmpty())
        {
            --mLives;
            mGameObjectManager->resetBallList();
        }
        if (hasFinished() && gameState != GameState::QUIT) gameState = GameState::END;
    }
}

void GameLevel::render(SDL_Renderer *renderer) const
{
    mGameObjectManager->render(renderer);
}


void GameLevel::newLevel()
{
    init();
}

void GameLevel::loadLevel()
{
    // TODO: Load saved level from disk.
}

void GameLevel::saveLevel()
{
    // TODO: Save current level to disk.
    if (!std::filesystem::exists("save")) std::filesystem::create_directory("save");
    std::ofstream saveFile("save/lives.txt");
    if (saveFile.is_open()) saveFile << mLives;
    saveFile.close();
}

