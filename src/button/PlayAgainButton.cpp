#include "button/PlayAgainButton.hpp"

#include "managers/GameEventManager.hpp"


void PlayAgainButton::onClick(GameState &gameState)
{
    gameState = GameState::PLAYING;
    GameEventManager::getInstance().pushEvent("play_again");
    resetButtonState();
}
