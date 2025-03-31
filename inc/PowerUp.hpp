#ifndef POWERUP_HPP
#define POWERUP_HPP


#include <SDL.h>

#include "defs.hpp"


enum class PowerUpStatus
{
    ACTIVATED,
    DEACTIVATED,
};

class PowerUp
{
public:
    explicit PowerUp(PowerUpDropType type);
    void update(int deltaTime);

    [[nodiscard]] PowerUpDropType getType() const {return mType;}
    [[nodiscard]] PowerUpStatus getStatus() const {return mStatus;}
    void setType(PowerUpDropType type) {mType = type;}
    void setStatus(PowerUpStatus status) {mStatus = status;}
protected:
    double mDuration = 0;
    int mElapsedTime = 0;
    PowerUpStatus mStatus = PowerUpStatus::ACTIVATED;
    PowerUpDropType mType;
};


#endif //POWERUP_HPP
