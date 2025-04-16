#ifndef POWERUP_HPP
#define POWERUP_HPP


#include "defs.hpp"


enum class PowerUpStatus
{
    ACTIVATED,
    DEACTIVATED,
};

class PowerUp
{
public:
    explicit PowerUp(PowerUpType type);
    PowerUp(const PowerUp& other);
    void update(int deltaTime);

    [[nodiscard]] PowerUpType getType() const {return mType;}
    [[nodiscard]] PowerUpStatus getStatus() const {return mStatus;}
    void setType(PowerUpType type) {mType = type;}
    void setStatus(PowerUpStatus status) {mStatus = status;}
private:
    double mDuration = 0;
    int mElapsedTime = 0;
    PowerUpStatus mStatus = PowerUpStatus::ACTIVATED;
    PowerUpType mType;
};


#endif //POWERUP_HPP
