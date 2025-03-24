#ifndef POWERUP_HPP
#define POWERUP_HPP


#include <SDL.h>

#include "defs.hpp"


enum class PowerUpStatus
{
    INACTIVE,
    ACTIVATED,
    DEACTIVATED,
};

class PowerUp
{
public:
    explicit PowerUp(PowerUpDropType type) : mType(type) {}
    void activate();
    void deactivate();
    void update();

    [[nodiscard]] PowerUpDropType getType() const {return mType;}
    [[nodiscard]] PowerUpStatus getStatus() const {return mStatus;}
protected:
    double mDuration = 0;
    Uint32 mStartTime = 0;
    PowerUpStatus mStatus = PowerUpStatus::INACTIVE;
    PowerUpDropType mType;
};


#endif //POWERUP_HPP
