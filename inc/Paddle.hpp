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
private:
    int mVel = 0;
};

#endif //PADDLE_HPP
