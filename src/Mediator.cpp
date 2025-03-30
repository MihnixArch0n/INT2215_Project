#include "Mediator.hpp"
#include "managers/GameObjectManager.hpp"
#include "managers/PowerUpManager.hpp"


void Mediator::init(GameObjectManager *objManager, PowerUpManager *powerUpManager)
{
    pGameObjectManager = objManager;
    pPowerUpManager = powerUpManager;
}


void Mediator::notify(PowerUpDropType type, const std::string& action)
{
    if (action == "collect")
    {
        pPowerUpManager->addPowerUp(type);
    }
    else if (action == "activate")
    {
        auto ballList = pGameObjectManager->getBallList();
        if (type == PowerUpDropType::MULTI_BALL)
        {
            for (int i = ballList.size() - 1; i >= 0; --i)
            {
                pGameObjectManager->addBall(ballList[i], ballList[i].getPosX()-50, ballList[i].getPosY());
                pGameObjectManager->addBall(ballList[i], ballList[i].getPosX()+50, ballList[i].getPosY());
            }
        }
        else if (type == PowerUpDropType::FIRE_BALL)
        {
            for (int i = ballList.size() - 1; i >= 0; --i)
                pGameObjectManager->makeFireBall(i);
        }
    }
    else if (action == "deactivate")
    {
        auto ballList = pGameObjectManager->getBallList();
        for (int i = ballList.size() - 1; i >= 0; --i)
            pGameObjectManager->makeNormalBall(i);
    }
}