#ifndef POWERUPMANAGER_HPP
#define POWERUPMANAGER_HPP


#include "defs.hpp"
#include "PowerUp.hpp"
#include "GameManager.hpp"


class PowerUpManager : public GameManager
{
public:
    void init(Mediator* mediator);
    void addPowerUp(PowerUpDropType type);
    void update();
    void applyEffect(PowerUpDropType type) const;
    void removeEffect(PowerUpDropType type) const;
    void activate(PowerUpDropType type);
    void deactivate(PowerUpDropType type);
    void reset();

    [[nodiscard]] ManagerType getType() const override {return ManagerType::POWER_UP_MANAGER;}
private:
    PowerUp* mCurrentPowerUp = nullptr;
    PowerUp* mMultiBallPowerUp = nullptr;
};


#endif //POWERUPMANAGER_HPP
