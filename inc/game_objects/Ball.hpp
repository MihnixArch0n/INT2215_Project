#ifndef BALL_HPP
#define BALL_HPP


#include <vector>
#include <memory>

#include "game_objects/GameObject.hpp"
#include "game_objects/Paddle.hpp"
#include "PowerUp.hpp"


class Brick;

enum class BallState
{
    START,
    MOVING,
    EXPIRED,
    DEAD
};

class Ball : public GameObject
{
public:
    Ball();
    explicit Ball(BallType type);
    Ball(const Ball& other);
    Ball(const Ball& other, BallType type);
    Ball(const Ball& other, int x, int y);
    ~Ball() override = default;

    static void init(ResourceManager &manager);
    void setObjectTexture(const ResourceManager &manager) override;

    void handleEvent(const SDL_Event& event);
    virtual void update(int deltaTime, const Paddle& paddle);

    [[nodiscard]] BallState getState() const;
    void setState(BallState state);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::BALL;}

    void onCollision(GameObject &other, int deltaTime) override;

    void save(std::ofstream &saveFile) const override;
    void load(std::ifstream &loadFile) override;

    constexpr static int BALL_SPEED = 400;
    constexpr static int BALL_WIDTH = 24;
    constexpr static int BALL_HEIGHT = 24;
protected:
    double mVelX = 0, mVelY = 0;
    BallState mState = BallState::START;
    std::unique_ptr<PowerUp> mPowerUp;
};


#endif //BALL_HPP
