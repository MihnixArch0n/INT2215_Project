#include "button/BackButton.hpp"

BackButton::BackButton(std::function<void()> callback) : backToNormalMenu(callback)
{
    mText = "Back";
}


void BackButton::onClick(GameState &gameState)
{
    backToNormalMenu();
    resetButtonState();
}
