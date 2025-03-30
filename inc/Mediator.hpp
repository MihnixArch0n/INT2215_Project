#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP


#include <string>

#include "defs.hpp"
#include "managers/GameManager.hpp"


class GameManager;
class GameObjectManager;
class PowerUpManager;

class Mediator
{
public:
    void notify(PowerUpDropType type, const std::string& action);
    void init(GameObjectManager* objManager, PowerUpManager* powerUpManager);
private:
    GameObjectManager* pGameObjectManager = nullptr;
    PowerUpManager* pPowerUpManager = nullptr;
};


#endif //MEDIATOR_HPP
