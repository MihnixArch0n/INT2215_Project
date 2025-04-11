#include "managers/GameEventManager.hpp"

GameEventManager &GameEventManager::getInstance()
{
    static GameEventManager instance;
    return instance;
}
