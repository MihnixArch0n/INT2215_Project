#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP


#include <SDL.h>
#include <vector>

#include "ResourceManager.hpp"
#include "game_objects/Ball.hpp"
#include "game_objects/Paddle.hpp"
#include "game_objects/Brick.hpp"
#include "game_objects/PowerUpDrop.hpp"
#include "GameManager.hpp"


class GameObjectManager : public GameManager
{
public:
    explicit GameObjectManager(const ResourceManager* manager);

    void init(Mediator* mediator);
    void handleEvent(const SDL_Event& event);
    void update(int deltaTime);
    void render(SDL_Renderer* renderer) const;

    [[nodiscard]] const std::vector<Ball>& getBallList() const {return mBallList;}
    void addBall(const Ball& ball, double x = 0, double y = 0);
    void makeFireBall(int index);
    void makeNormalBall(int index);

    [[nodiscard]] bool ballListEmpty() const {return mBallList.empty();}
    [[nodiscard]] bool brickListEmpty() const {return mBricksList.empty();}


    void spawnDrop(PowerUpDropType type, double x, double y);
    void resetBallList();

    [[nodiscard]] ManagerType getType() const override {return ManagerType::GAME_OBJECT_MANAGER;}
private:
    Paddle mPaddle;
    std::vector<Ball> mBallList;
    std::vector<Brick> mBricksList;
    std::vector<PowerUpDrop> mPowerUpDropList;
    const ResourceManager& rResourceManager;
};


#endif //GAMEOBJECTMANAGER_HPP
