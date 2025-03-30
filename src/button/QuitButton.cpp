#include "button/QuitButton.hpp"


void QuitButton::onClick(GameState &gameState)
{
    gameState = GameState::QUIT_TO_START;
    resetButtonState();
}
