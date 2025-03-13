#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>

#include "GameObject.hpp"

class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle() override = default;

    constexpr static int M_SPEED = 5;

    void handleEvent(const SDL_Event& e);
    void update();

    constexpr static int M_PADDLE_WIDTH = 100;
    constexpr static int M_PADDLE_HEIGHT = 30;
private:
    int mVel = 0;
};

#endif //PADDLE_HPP
