#ifndef POWERUP_HPP
#define POWERUP_HPP


#include <fstream>

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

    [[nodiscard]] double getElapsedTime() const {return mElapsedTime;}
    void setElapsedTime(double time) {mElapsedTime = time;}

    void save(std::ofstream& saveFile);
    void load(std::ifstream& loadFile);
private:
    double mDuration = 0;
    double mElapsedTime = 0;
    PowerUpStatus mStatus = PowerUpStatus::ACTIVATED;
    PowerUpType mType;
};


#endif //POWERUP_HPP
