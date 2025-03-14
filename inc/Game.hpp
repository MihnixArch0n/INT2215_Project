#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <SDL.h>

#include "RenderWindow.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Brick.hpp"

class Game
{
public:
    explicit Game(RenderWindow* renderWindow);
    [[nodiscard]] SDL_Renderer* getRenderer() const;

    [[nodiscard]] bool hasFinished() const;
    [[nodiscard]] bool hasLost() const;
    [[nodiscard]] bool hasWon() const;
    void init(MyTexture* paddleTexture, MyTexture* ballTexture, MyTexture* brickTexture);
    void handleEvent();
    void update();
    void render() const;
private:
    bool finished = false;
    int mLives = 3;
    int lastUpdateTime, currentTime;
    RenderWindow* mRenderWindow;
    Paddle mPaddle;
    Ball mBall;
    std::vector<Brick> mBricksList;
};

#endif //GAME_HPP
