#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>

#include "GameObject.hpp"

class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle() override = default;

    constexpr static int M_PADDLE_SPEED = 500;

    void handleEvent(const SDL_Event& e);
    void update(int deltaTime);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::PADDLE;}
    void onCollision(GameObject &other, int deltaTime) override {}

    constexpr static int M_PADDLE_WIDTH = 100;
    constexpr static int M_PADDLE_HEIGHT = 30;
private:
    double mVel = 0;
};

#endif //PADDLE_HPP
