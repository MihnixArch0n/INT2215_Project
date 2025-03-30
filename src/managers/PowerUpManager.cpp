#include "managers/PowerUpManager.hpp"
#include "PowerUp.hpp"
#include "Mediator.hpp"


void PowerUpManager::init(Mediator* mediator) {pMediator = mediator;}

void PowerUpManager::addPowerUp(PowerUpDropType type)
{
    if (type == PowerUpDropType::MULTI_BALL)
    {
        delete mMultiBallPowerUp;
        mMultiBallPowerUp = new PowerUp(type);
    }
    else
    {
        delete mCurrentPowerUp;
        mCurrentPowerUp = new PowerUp(type);
    }
}

void PowerUpManager::update()
{
    if (mCurrentPowerUp != nullptr)
    {
        if (mCurrentPowerUp->getStatus() == PowerUpStatus::INACTIVE)
            activate(mCurrentPowerUp->getType());
        else if (mCurrentPowerUp->getStatus() == PowerUpStatus::ACTIVATED)
            mCurrentPowerUp->update();
        else if (mCurrentPowerUp->getStatus() == PowerUpStatus::DEACTIVATED)
            deactivate(mCurrentPowerUp->getType());
    }

    if (mMultiBallPowerUp != nullptr)
    {
        if (mMultiBallPowerUp->getStatus() == PowerUpStatus::INACTIVE)
            activate(PowerUpDropType::MULTI_BALL);
        else if (mMultiBallPowerUp->getStatus() == PowerUpStatus::ACTIVATED)
            mMultiBallPowerUp->update();
        else if (mMultiBallPowerUp->getStatus() == PowerUpStatus::DEACTIVATED)
            deactivate(PowerUpDropType::MULTI_BALL);
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

void PowerUpManager::activate(PowerUpDropType type)
{
    if (type == PowerUpDropType::MULTI_BALL)
    {
        mMultiBallPowerUp->setStatus(PowerUpStatus::ACTIVATED);
        mMultiBallPowerUp->setType(PowerUpDropType::MULTI_BALL);
        applyEffect(PowerUpDropType::MULTI_BALL);
    }
    else
    {
        mCurrentPowerUp->setStatus(PowerUpStatus::ACTIVATED);
        mCurrentPowerUp->setType(type);
        applyEffect(type);
    }
}

void PowerUpManager::deactivate(PowerUpDropType type)
{
    removeEffect(type);
    if (type != PowerUpDropType::MULTI_BALL)
    {
        delete mCurrentPowerUp;
        mCurrentPowerUp = nullptr;
    }
    else
    {
        delete mMultiBallPowerUp;
        mMultiBallPowerUp = nullptr;
    }
}

void PowerUpManager::reset()
{
    delete mCurrentPowerUp;
    mCurrentPowerUp = nullptr;
    delete mMultiBallPowerUp;
    mMultiBallPowerUp = nullptr;
}
