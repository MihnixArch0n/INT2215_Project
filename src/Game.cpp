#include <iostream>

#include "defs.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "CollisionManager.hpp"
#include "AudioManager.hpp"


Game::Game()
{
    lastUpdateTime = currentTime = 0;
    mBricksList.resize(5);
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
    mPaddle.setObjectTexture(mResourceManager.getPaddleTexture());
    mBall.setObjectTexture(mResourceManager.getBallTexture());
    for (int i = 0; i < 5; i++)
    {
        mBricksList[i].setObjectTexture(mResourceManager.getBrickTexture());
    }
    lastUpdateTime = SDL_GetTicks();
    return true;
}


void Game::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) finished = true;
        mPaddle.handleEvent(event);
        mBall.handleEvent(event);
    }
}

void Game::update()
{
    currentTime = SDL_GetTicks();
    int deltaTime = currentTime - lastUpdateTime;
    mPaddle.update(deltaTime);
    mBall.update(deltaTime, mPaddle);
    CollisionManager::handleCollision(mBall, mPaddle, deltaTime);
    int bricksLeft = mBricksList.size();
    for (int i = bricksLeft-1; i >= 0; --i)
    {
        CollisionManager::handleCollision(mBall, mBricksList[i], deltaTime);
        if (!mBricksList[i].isAlive()) mBricksList.erase(mBricksList.begin() + i);
    }
    if (mBall.getState() == DEAD)
    {
        --mLives;
        mBall.setState(START);
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
        mPaddle.render(renderer);
        mBall.render(renderer);
        for (const auto &it : mBricksList)
        {
            it.render(renderer);
        }
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
bool Game::hasWon() const {return mBricksList.empty();}
bool Game::hasFinished() const {return hasLost() || hasWon() || finished;}