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

void GameLevel::loadLevel()
{
    if (std::filesystem::exists("save"))
    {
        std::ifstream saveFile("save/lives");
        saveFile >> mLives;
        saveFile.close();

        mGameObjectManager->load();
    }
}

void GameLevel::saveLevel()
{
    std::filesystem::create_directory("save");
    std::ofstream saveFile("save/lives.txt");
    if (saveFile.is_open()) saveFile << mLives;
    saveFile.close();

    mGameObjectManager->save();
}

