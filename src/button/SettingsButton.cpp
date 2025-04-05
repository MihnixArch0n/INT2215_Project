#include "button/SettingsButton.hpp"


SettingsButton::SettingsButton(std::function<void()> callback) : goToSettingMenu(callback)
{
    mText = "Settings";
}

void SettingsButton::onClick(GameState &gameState)
{
    goToSettingMenu();
    resetButtonState();
}

