#include "button/LoadButton.hpp"
#include "managers/GameEventManager.hpp"


void LoadButton::onClick(GameState &gameState)
{
    GameEventManager::getInstance().pushEvent("load");
    resetButtonState();
}
