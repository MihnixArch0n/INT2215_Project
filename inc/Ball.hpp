#ifndef BALL_HPP
#define BALL_HPP


#include <vector>

#include "GameObject.hpp"
#include "Paddle.hpp"


class Brick;

enum BallState
{
    START,
    MOVING,
    DEAD
};

class Ball : public GameObject
{
public:
    Ball();
    ~Ball() override = default;

    void handleEvent(const SDL_Event& event);
    void update(const Paddle& paddle, const std::vector<Brick>& bricksList);

    void handleCollision(const Paddle& paddle, const std::vector<Brick>& bricksList);
    void handleCollisionWithPaddle(const Paddle& paddle);
    void handleCollisionWithBricks(const std::vector<Brick>& bricksList);

    [[nodiscard]] BallState getState() const;
    void setState(BallState state);

    constexpr static int M_BALL_SPEED = 5;
    constexpr static int M_BALL_WIDTH = 32;
    constexpr static int M_BALL_HEIGHT = 32;
private:
    double mVelX = 0, mVelY = 0;
    BallState mState = START;
};


#endif //BALL_HPP
