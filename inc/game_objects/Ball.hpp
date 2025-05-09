#ifndef BALL_HPP
#define BALL_HPP


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
    Ball(const Ball& other);
    Ball(const Ball& other, double x, double y);
    ~Ball() override = default;

    static void init(ResourceManager &manager);

    void handleEvent(const SDL_Event& event);
    void update(int deltaTime, const Paddle& paddle);

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
};


#endif //BALL_HPP
