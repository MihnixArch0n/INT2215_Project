#ifndef FIREBALL_HPP
#define FIREBALL_HPP


#include "game_objects/Ball.hpp"
#include "PowerUp.hpp"


class FireBall : public Ball
{
public:
    FireBall();
    explicit FireBall(const Ball& other);

    void update(int deltaTime, const Paddle &paddle) override;
private:
    PowerUp mPowerUp;
};



#endif //FIREBALL_HPP
