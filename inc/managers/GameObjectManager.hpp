#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP


#include <SDL.h>
#include <vector>
#include <memory>

#include "ResourceManager.hpp"
#include "game_objects/Ball.hpp"
#include "game_objects/Paddle.hpp"
#include "game_objects/Brick.hpp"
#include "game_objects/PowerUpDrop.hpp"


class GameObjectManager
{
public:
    explicit GameObjectManager(ResourceManager& manager);

    void init();
    void handleEvent(const SDL_Event& event);
    void update(int deltaTime);
    void render(SDL_Renderer* renderer) const;

    void addBall(const Ball& ball, double x = 0, double y = 0);
    void changeBall(const std::unique_ptr<Ball>& ball, BallType ballType) const;

    [[nodiscard]] bool ballListEmpty() const {return mBallList.empty();}
    [[nodiscard]] bool brickListEmpty() const;

    [[nodiscard]] PowerUpType getCollectedPowerUp() const;
    void applyPowerUp(PowerUpType type);
    void removePowerUp(PowerUpType type) const;

    void spawnDrop(double x, double y);
    void resetBallList();

    void save() const;
    void load();

private:
    Paddle mPaddle;
    std::vector<std::unique_ptr<Ball>> mBallList;
    std::vector<std::vector<Brick>> mBricksList;
    std::vector<PowerUpDrop> mPowerUpDropList;
    ResourceManager& rResourceManager;
};


#endif //GAMEOBJECTMANAGER_HPP
