#include <iostream>
#include "Game.hpp"


Game::Game(RenderWindow* renderWindow) : mRenderWindow(renderWindow)
{
    lastUpdateTime = currentTime = 0;
    mBricksList.resize(5);
}


void Game::init(MyTexture* paddleTexture, MyTexture* ballTexture, MyTexture* brickTexture)
{
    mPaddle.setObjectTexture(paddleTexture);
    mBall.setObjectTexture(ballTexture);
    for (int i = 0; i < 5; i++)
    {
        mBricksList[i].setObjectTexture(brickTexture);
    }
    lastUpdateTime = SDL_GetTicks();
}


SDL_Renderer* Game::getRenderer() const {return mRenderWindow->getRenderer();}


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
    mBall.update(deltaTime, mPaddle, mBricksList);
    int bricksLeft = mBricksList.size();
    for (int i = bricksLeft-1; i >= 0; --i)
    {
        mBricksList[i].update(mBall);
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
    SDL_Renderer* renderer = mRenderWindow->getRenderer();
    SDL_RenderClear(renderer);
    mPaddle.render(renderer);
    mBall.render(renderer);
    for (const auto &it : mBricksList)
    {
        it.render(renderer);
    }
    SDL_RenderPresent(renderer);
    if (hasWon()) std::cout << "You won" << std::endl;
    if (hasLost()) std::cout << "You lost" << std::endl;
}

bool Game::hasLost() const {return mLives <= 0;}
bool Game::hasWon() const {return mBricksList.empty();}
bool Game::hasFinished() const {return hasLost() || hasWon() || finished;}