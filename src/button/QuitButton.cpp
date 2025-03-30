#include "button/QuitButton.hpp"


void QuitButton::onClick(GameState &gameState)
{
    gameState = GameState::START;
    resetButtonState();
}
