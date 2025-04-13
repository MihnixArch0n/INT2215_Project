#ifndef GAMELEVEL_HPP
#define GAMELEVEL_HPP


#include <SDL.h>

#include "managers/GameObjectManager.hpp"


class GameLevel
{
public:
    explicit GameLevel(ResourceManager& manager);

    void init(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& event);
    void update(int deltaTime, GameState& gameState);
    void render(SDL_Renderer* renderer) const;

    [[nodiscard]] bool hasLost() const {return mLives <= 0;}
    [[nodiscard]] bool hasWon() const {return mGameObjectManager->brickListEmpty();}
    [[nodiscard]] bool hasFinished() const {return hasLost() || hasWon();}

    void saveLevel();
    void loadLevel();
private:
    int mLives = 3;

    std::unique_ptr<GameObjectManager> mGameObjectManager;
    ResourceManager& rResourceManager;

    const MyTexture* liveTexture = nullptr;
};


#endif //GAMELEVEL_HPP
