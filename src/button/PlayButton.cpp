#include "button/PlayButton.hpp"


void PlayButton::onClick(GameState &gameState)
{
    gameState = GameState::PLAYING;
    resetButtonState();
}
