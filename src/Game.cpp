#include <iostream>

#include "defs.hpp"
#include "Game.hpp"

#include "managers/GameEventManager.hpp"
#include "managers/ResourceManager.hpp"
#include "managers/AudioManager.hpp"


Game::Game()
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

    Ball::init(mResourceManager);
    Brick::init(mResourceManager);
    Paddle::init(mResourceManager);
    PowerUpDrop::init(mResourceManager);

    AudioManager::getInstance().init(mResourceManager);
    AudioManager::getInstance().getMusic().play();
    mGameLevel = new GameLevel(mResourceManager);
    mGameLevel->init(mRenderWindow.getRenderer());
    mMenuManager.init(mResourceManager, mRenderWindow.getRenderer());
    lastUpdateTime = static_cast<int>(SDL_GetTicks());
    return true;
}


void Game::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) mState = GameState::QUIT;
        mMenuManager.handleEvents(event, mState);
        if (mState == GameState::PLAYING) mGameLevel->handleEvent(event);
    }

    while (!GameEventManager::getInstance().isEmpty())
    {
        auto gameEvent = GameEventManager::getInstance().topEvent();
        if (gameEvent == "play_again") mGameLevel->init(mRenderWindow.getRenderer());
        else if (gameEvent == "save") mGameLevel->saveLevel();
        else if (gameEvent == "load")
        {
            mGameLevel->loadLevel();
            mState = GameState::PLAYING;
        }

        GameEventManager::getInstance().popEvent();
    }
}

void Game::update()
{
    currentTime = static_cast<int>(SDL_GetTicks());
    int deltaTime = currentTime - lastUpdateTime;
    mMenuManager.update(mState);
    if (mState == GameState::QUIT_TO_START)
    {
        delete mGameLevel;
        mGameLevel = new GameLevel(mResourceManager);
        mGameLevel->init(mRenderWindow.getRenderer());
    }
    if (mState == GameState::QUIT_TO_START) mState = GameState::START;
    if (mState == GameState::PLAYING) mGameLevel->update(deltaTime, mState);

    lastUpdateTime = currentTime;
    // SDL_Delay(10);
}

void Game::render() const
{
    SDL_Renderer* renderer = mRenderWindow.getRenderer();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    mMenuManager.render(renderer);
    if (mState == GameState::PLAYING) mGameLevel->render(renderer);
    if (mState == GameState::END)
    {
        if (mGameLevel->hasLost())
            mResourceManager.getLostTexture().render(0, SCREEN_HEIGHT/2, renderer);
        else if (mGameLevel->hasWon())
            mResourceManager.getWonTexture().render(0, SCREEN_HEIGHT/2, renderer);
    }
    SDL_RenderPresent(renderer);
}

void Game::loop()
{
    if (init())
    {
        while (mState != GameState::QUIT)
        {
            handleEvent();
            update();
            render();
        }
    }
    else std::cerr << "Failed to init game" << std::endl;
}
