#ifndef BALL_HPP
#define BALL_HPP


#include <vector>

#include "GameObject.hpp"
#include "Paddle.hpp"


class Brick;

enum class BallState
{
    START,
    MOVING,
    DEAD
};

class Ball : public GameObject
{
public:
    Ball();
    Ball(const Ball& other, int x, int y);
    ~Ball() override = default;

    void handleEvent(const SDL_Event& event);
    void update(int deltaTime, const Paddle& paddle);

    void handleCollision(int deltaTime, const Paddle& paddle, const std::vector<Brick>& bricksList);
    void handleCollisionWithPaddle(int deltaTime, const Paddle& paddle);
    void handleCollisionWithBricks(int deltaTime, const std::vector<Brick>& bricksList);

    [[nodiscard]] BallState getState() const;
    void setState(BallState state);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::BALL;}

    void onCollision(GameObject &other, int deltaTime) override;

    constexpr static int M_BALL_SPEED = 450;
    constexpr static int M_BALL_WIDTH = 32;
    constexpr static int M_BALL_HEIGHT = 32;
private:
    double mVelX = 0, mVelY = 0;
    BallState mState = BallState::START;
};


#endif //BALL_HPP
