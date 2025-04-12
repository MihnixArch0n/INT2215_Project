#include "menu/StartMenu.hpp"

#include <iostream>
#include <ostream>


#include "button/PlayButton.hpp"
#include "button/LoadButton.hpp"
#include "button/SettingsButton.hpp"
#include "button/ExitGameButton.hpp"


StartMenu::StartMenu(std::function<void()> callback) : setSettingGroup(callback) {}

bool StartMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    mButtonList.push_back(std::make_unique<PlayButton>());
    mButtonList.push_back(std::make_unique<LoadButton>());
    mButtonList.push_back(std::make_unique<SettingsButton>(setSettingGroup));
    mButtonList.push_back(std::make_unique<ExitGameButton>());
    return Menu::init(manager, renderer);
}

void StartMenu::handleEvents(SDL_Event &event, GameState& gameState)
{
    if (gameState == GameState::START) Menu::handleEvents(event, gameState);
}

void StartMenu::update(GameState &gameState)
{
    if (gameState == GameState::START)
    {
        hidden = false;
        Menu::update(gameState);
    }
    else hidden = true;
}

