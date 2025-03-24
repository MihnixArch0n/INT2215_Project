#ifndef POWERUPMANAGER_HPP
#define POWERUPMANAGER_HPP


#include <vector>

#include "defs.hpp"
#include "PowerUp.hpp"
#include "GameManager.hpp"


class PowerUpManager : public GameManager
{
public:
    void init(Mediator* mediator);
    void addPowerUp(PowerUpDropType type);
    void spawnDrop();
    void update();
    void applyEffect(PowerUpDropType type) const;
    void removeEffect(PowerUpDropType type) const;

    [[nodiscard]] ManagerType getType() const override {return ManagerType::POWER_UP_MANAGER;}
private:
    std::vector<PowerUp> mPowerUpList;
};



#endif //POWERUPMANAGER_HPP
