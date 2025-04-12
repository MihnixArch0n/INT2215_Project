#include "button/SaveButton.hpp"

#include "managers/GameEventManager.hpp"


void SaveButton::onClick(GameState &gameState)
{
    GameEventManager::getInstance().pushEvent("save");
    resetButtonState();
}

