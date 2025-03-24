#include "Mediator.hpp"
#include "GameObjectManager.hpp"
#include "PowerUpManager.hpp"


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
        if (type == PowerUpDropType::MULTI_BALL)
        {
            auto ballList = pGameObjectManager->getBallList();
            for (int i = ballList.size() - 1; i >= 0; --i)
            {
                pGameObjectManager->addBall(ballList[i], ballList[i].getPosX()-50, ballList[i].getPosY());
                pGameObjectManager->addBall(ballList[i], ballList[i].getPosX()+50, ballList[i].getPosY());
            }
        }
    }
}