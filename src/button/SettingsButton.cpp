#include "button/SettingsButton.hpp"


void SettingsButton::onClick(GameState &gameState)
{
    gameState = GameState::SETTINGS;
    resetButtonState();
}
