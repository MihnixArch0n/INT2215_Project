#include <iostream>

#include "defs.hpp"
#include "Game.hpp"
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

    AudioManager::getInstance().init(mResourceManager.getMusic(),
        mResourceManager.getSound());
    AudioManager::getInstance().getMusic().play();
    mGameLevel = new GameLevel(&mResourceManager);
    mGameLevel->init();
    mMenuManager.init(mResourceManager, mRenderWindow.getRenderer());
    lastUpdateTime = SDL_GetTicks();
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
}

void Game::update()
{
    currentTime = SDL_GetTicks();
    int deltaTime = currentTime - lastUpdateTime;
    mMenuManager.update(mState);
    if (mState == GameState::QUIT_TO_START || mGameLevel->hasFinished())
    {
        delete mGameLevel;
        mGameLevel = new GameLevel(&mResourceManager);
        mGameLevel->init();
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
