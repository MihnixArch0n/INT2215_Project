#include "managers/ConfigManager.hpp"


ConfigManager &ConfigManager::getInstance()
{
    static ConfigManager instance;
    return instance;
}

