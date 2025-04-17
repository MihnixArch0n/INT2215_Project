#include "button/SettingsButton.hpp"

#include <utility>


SettingsButton::SettingsButton(std::function<void()> callback) :
    goToSettingMenu(std::move(callback))
{
    mText = "Settings";
}

void SettingsButton::onClick(GameState &gameState)
{
    goToSettingMenu();
    resetButtonState();
}

