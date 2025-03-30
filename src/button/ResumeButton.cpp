#include "button/ResumeButton.hpp"


void ResumeButton::onClick(GameState &gameState)
{
    gameState = GameState::PLAYING;
    resetButtonState();
}
