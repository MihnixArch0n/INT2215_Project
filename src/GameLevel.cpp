#include "GameLevel.hpp"

#include <filesystem>
#include <fstream>


GameLevel::GameLevel(ResourceManager& manager) : rResourceManager(manager)
{
}

void GameLevel::init(SDL_Renderer* renderer)
{
    mGameObjectManager = std::make_unique<GameObjectManager>(rResourceManager);
    mGameObjectManager->init();
    mLives = 3;
    rResourceManager.addText("Live", renderer);
    liveTexture = rResourceManager.getText("Live");
}

void GameLevel::handleEvent(const SDL_Event &event) const
{
    mGameObjectManager->handleEvent(event);
}

void GameLevel::update(int deltaTime, GameState& gameState)
{
    if (!hasFinished())
    {
        mGameObjectManager->update(deltaTime);

        if (mCurrentPowerUp != nullptr)
        {
            mCurrentPowerUp->update(deltaTime);

            if (mCurrentPowerUp->getStatus() == PowerUpStatus::DEACTIVATED)
            {
                mGameObjectManager->removePowerUp(mCurrentPowerUp->getType());
                mCurrentPowerUp.reset();
            }
        }
        auto collectedPowerUp = mGameObjectManager->getCollectedPowerUp();
        if (collectedPowerUp != PowerUpType::TOTAL)
        {
            mCurrentPowerUp = std::make_unique<PowerUp>(collectedPowerUp);
            mGameObjectManager->applyPowerUp(collectedPowerUp);
        }

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, LEVEL_WIDTH, 0, LEVEL_WIDTH, LEVEL_HEIGHT);
    liveTexture->render(LEVEL_WIDTH, 0, renderer);
    auto live = "0" + std::to_string(mLives);
    rResourceManager.getText(live)->render(LEVEL_WIDTH, liveTexture->getHeight(), renderer);
}

void GameLevel::loadLevel()
{
    if (std::filesystem::exists("save"))
    {
        std::ifstream loadFile("save/level.txt");
        loadFile >> mLives;
        int tmp;
        loadFile >> tmp;
        if (tmp == 1)
        {
            mCurrentPowerUp = std::make_unique<PowerUp>(PowerUpType::TOTAL);
            mCurrentPowerUp->load(loadFile);
        }
        loadFile.close();

        mGameObjectManager->load();
    }
}

void GameLevel::saveLevel() const
{
    std::filesystem::create_directory("save");
    std::ofstream saveFile("save/level.txt");
    if (saveFile.is_open())
    {
        saveFile << mLives << std::endl;
        if (mCurrentPowerUp != nullptr)
        {
            saveFile << 1 << " ";
            mCurrentPowerUp->save(saveFile);
        }
        else saveFile << "0" << std::endl;
    }
    saveFile.close();

    mGameObjectManager->save();
}

