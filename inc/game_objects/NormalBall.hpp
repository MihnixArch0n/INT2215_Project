#ifndef NORMALBALL_HPP
#define NORMALBALL_HPP


#include "game_objects/Ball.hpp"


class NormalBall : public Ball
{
public:
    NormalBall() {mSubType = BallType::NORMAL;}
    explicit NormalBall(const Ball& other) : Ball(other) {}
};



#endif //NORMALBALL_HPP
