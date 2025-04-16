#ifndef GAMELEVEL_HPP
#define GAMELEVEL_HPP


#include <SDL.h>

#include "managers/GameObjectManager.hpp"


class GameLevel
{
public:
    explicit GameLevel(ResourceManager& manager);

    void init(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event) const;
    void update(int deltaTime, GameState& gameState);
    void render(SDL_Renderer* renderer) const;

    [[nodiscard]] bool hasLost() const {return mLives <= 0;}
    [[nodiscard]] bool hasWon() const {return mGameObjectManager->brickListEmpty();}
    [[nodiscard]] bool hasFinished() const {return hasLost() || hasWon();}

    void saveLevel() const;
    void loadLevel();
private:
    int mLives = 3;

    std::unique_ptr<GameObjectManager> mGameObjectManager;
    std::unique_ptr<PowerUp> mCurrentPowerUp;
    ResourceManager& rResourceManager;

    const MyTexture* liveTexture = nullptr;
};


#endif //GAMELEVEL_HPP
