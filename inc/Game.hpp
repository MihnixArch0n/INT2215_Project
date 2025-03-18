#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <SDL.h>

#include "RenderWindow.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Brick.hpp"
#include "ResourceManager.hpp"

class Game
{
public:
    Game();

    [[nodiscard]] bool hasFinished() const;
    [[nodiscard]] bool hasLost() const;
    [[nodiscard]] bool hasWon() const;
    bool init();
    void handleEvent();
    void update();
    void render() const;
    void loop();
private:
    bool finished = false;
    int mLives = 3;
    int lastUpdateTime, currentTime;
    RenderWindow mRenderWindow;
    Paddle mPaddle;
    Ball mBall;
    std::vector<Brick> mBricksList;
    ResourceManager mResourceManager;
};

#endif //GAME_HPP
