#include <iostream>

#include "defs.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "CollisionManager.hpp"
#include "AudioManager.hpp"


Game::Game() : mGameObjectManager(&mResourceManager)
{
    lastUpdateTime = currentTime = 0;
}


bool Game::init()
{
    if (!mRenderWindow.create(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        std::cerr << "Failed to create window" << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(mRenderWindow.getRenderer(), 255, 255, 255, 255);


    if (!mResourceManager.loadResource(mRenderWindow.getRenderer()))
    {
        std::cerr << "Failed to load resource " << std::endl;
        return false;
    }

    AudioManager::getInstance().init(mResourceManager.getMusic(),
        mResourceManager.getSound());
    mMediator.init(&mGameObjectManager, &mPowerUpManager);
    mGameObjectManager.init(&mMediator);
    mPowerUpManager.init(&mMediator);
    lastUpdateTime = SDL_GetTicks();
    return true;
}


void Game::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) finished = true;
        mGameObjectManager.handleEvent(event);
    }
}

void Game::update()
{
    currentTime = SDL_GetTicks();
    int deltaTime = currentTime - lastUpdateTime;
    mGameObjectManager.update(deltaTime);
    mPowerUpManager.update();
    if (mGameObjectManager.ballListEmpty())
    {
        --mLives;
        mGameObjectManager.resetBallList();
    }

    if (hasFinished()) finished = true;
    lastUpdateTime = currentTime;
    // SDL_Delay(10);
}

void Game::render() const
{
    SDL_Renderer* renderer = mRenderWindow.getRenderer();
    SDL_RenderClear(renderer);
    if (hasWon())
    {
        mResourceManager.getWonTexture().render(0, 0, mRenderWindow.getRenderer());
        std::cout << "You won" << std::endl;
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    else if (hasLost())
    {
        mResourceManager.getLostTexture().render(0, 0, mRenderWindow.getRenderer());
        std::cout << "You lost" << std::endl;
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    else
    {
        mGameObjectManager.render(renderer);
        SDL_RenderPresent(renderer);
    }
}

void Game::loop()
{
    if (init())
    {
        while (!hasFinished())
        {
            handleEvent();
            update();
            render();
        }
    }
    else std::cerr << "Failed to init game" << std::endl;
}

bool Game::hasLost() const {return mLives <= 0;}
// bool Game::hasWon() const {return mGameObjectManager.brickListEmpty();}
bool Game::hasWon() const {return false;}
bool Game::hasFinished() const {return hasLost() || hasWon() || finished;}