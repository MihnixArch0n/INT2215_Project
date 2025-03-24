#ifndef GAME_HPP
#define GAME_HPP


#include "RenderWindow.hpp"
#include "GameObjectManager.hpp"
#include "ResourceManager.hpp"
#include "PowerUpManager.hpp"
#include "Mediator.hpp"

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
    ResourceManager mResourceManager;
    PowerUpManager mPowerUpManager;
    GameObjectManager mGameObjectManager;
    Mediator mMediator;
};

#endif //GAME_HPP
