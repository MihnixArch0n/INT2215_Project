#ifndef GAME_HPP
#define GAME_HPP


#include "RenderWindow.hpp"
#include "managers/ResourceManager.hpp"
#include "managers/MenuManager.hpp"
#include "GameLevel.hpp"


class Game
{
public:
    Game();

    bool init();
    void handleEvent();
    void update();
    void render() const;
    void loop();
private:
    int lastUpdateTime, currentTime;

    GameState mState = GameState::START;

    RenderWindow mRenderWindow;
    ResourceManager mResourceManager;
    GameLevel mGameLevel;
    MenuManager mMenuManager;
};

#endif //GAME_HPP
