#include <iostream>
#include "MenuManager.hpp"
#include "menu/StartMenu.hpp"
#include "menu/EndMenu.hpp"
#include "menu/InGameMenu.hpp"


bool MenuManager::init(ResourceManager &resourceManager, SDL_Renderer* renderer)
{
    mMenuList.push_back(std::make_unique<StartMenu>());
    mMenuList.push_back(std::make_unique<InGameMenu>());
    mMenuList.push_back(std::make_unique<EndMenu>());

    for (auto &menu : mMenuList)
    {
        if (!menu->init(resourceManager, renderer))
        {
            std::cerr << "Failed to initialize menu!" << std::endl;
            return false;
        }
    }
    return true;
}

void MenuManager::handleEvents(SDL_Event &event, GameState& gameState)
{
    for (auto &menu : mMenuList) menu->handleEvents(event, gameState);
}


void MenuManager::update(GameState& gameState)
{
    for (auto &menu : mMenuList) menu->update(gameState);
}

void MenuManager::render(SDL_Renderer* renderer) const
{
    for (auto &menu : mMenuList) menu->render(renderer);
}
