#ifndef GAMELEVEL_HPP
#define GAMELEVEL_HPP


#include <SDL.h>

#include "managers/GameObjectManager.hpp"
#include "managers/PowerUpManager.hpp"
#include "Mediator.hpp"


class GameLevel
{
public:
    explicit GameLevel(const ResourceManager* manager);

    void init();
    void handleEvent(SDL_Event& event);
    void update(int deltaTime, GameState& gameState);
    void render(SDL_Renderer* renderer) const;
    void clear();
    void reset();

    [[nodiscard]] bool hasLost() const {return mLives <= 0;}
    [[nodiscard]] bool hasWon() const {return mGameObjectManager.brickListEmpty();}
    [[nodiscard]] bool hasFinished() const {return hasLost() || hasWon();}

    void newLevel();
    void saveLevel();
    void loadLevel();
private:
    int mLives = 3;

    GameObjectManager mGameObjectManager;
    PowerUpManager mPowerUpManager;
    Mediator mMediator;
};


#endif //GAMELEVEL_HPP
