#include "button/BackButton.hpp"

#include <utility>

BackButton::BackButton(std::function<void()> callback) :
    backToNormalMenu(std::move(callback))
{
    mText = "Back";
}


void BackButton::onClick(GameState &gameState)
{
    backToNormalMenu();
    resetButtonState();
}
