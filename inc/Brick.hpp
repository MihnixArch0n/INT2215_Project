#ifndef BRICK_HPP
#define BRICK_HPP


#include "GameObject.hpp"

class Ball;

class Brick : public GameObject
{
public:
    Brick();
    ~Brick() override = default;

    void update(const Ball& ball);
    [[nodiscard]] bool isAlive() const;
    constexpr static int BRICK_WIDTH = 40;
    constexpr static int BRICK_HEIGHT = 20;
private:
    bool alive = true;
};


#endif //BRICK_HPP
