#include "PowerUpManager.hpp"
#include "PowerUp.hpp"
#include "Mediator.hpp"


void PowerUpManager::init(Mediator* mediator) {pMediator = mediator;}

void PowerUpManager::addPowerUp(PowerUpDropType type)
{
    mPowerUpList.emplace_back(type);
}

void PowerUpManager::update()
{
    for (int i = mPowerUpList.size() - 1; i >= 0; --i)
    {
        if (mPowerUpList[i].getStatus() == PowerUpStatus::INACTIVE)
        {
            mPowerUpList[i].activate();
            applyEffect(mPowerUpList[i].getType());
        }
        else if (mPowerUpList[i].getStatus() == PowerUpStatus::DEACTIVATED)
        {
            mPowerUpList[i].deactivate();
            removeEffect(mPowerUpList[i].getType());
        }
        else mPowerUpList[i].update();
    }
}

void PowerUpManager::applyEffect(PowerUpDropType type) const
{
    pMediator->notify(type, "activate");
}

void PowerUpManager::removeEffect(PowerUpDropType type) const
{
    pMediator->notify(type, "deactivate");
}
