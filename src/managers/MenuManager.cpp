#include <iostream>
#include "managers/MenuManager.hpp"

#include "menu/StartMenu.hpp"
#include "menu/EndMenu.hpp"
#include "menu/InGameMenu.hpp"
#include "menu/SettingMenu.hpp"


bool MenuManager::init(ResourceManager &resourceManager, SDL_Renderer* renderer)
{
    mMenuList.push_back(std::make_unique<StartMenu>(setSettingGroup));
    mMenuList.push_back(std::make_unique<InGameMenu>(setSettingGroup));
    mMenuList.push_back(std::make_unique<EndMenu>());
    mSettingMenu = std::make_unique<SettingMenu>(setNormalGroup);
    mSettingMenu->init(resourceManager, renderer);

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

void MenuManager::handleEvents(SDL_Event &event, GameState& gameState) const
{
    if (mMenuGroup == MenuGroupType::SETTINGS) mSettingMenu->handleEvents(event, gameState);
    else
    {
        for (auto &menu : mMenuList) menu->handleEvents(event, gameState);
    }
}

void MenuManager::update(GameState& gameState) const
{
    if (mMenuGroup == MenuGroupType::SETTINGS) mSettingMenu->update(gameState);
    else
    {
        for (auto &menu : mMenuList) menu->update(gameState);
    }
}

void MenuManager::render(SDL_Renderer* renderer) const
{
    if (mMenuGroup == MenuGroupType::SETTINGS) mSettingMenu->render(renderer);
    else
    {
        for (auto &menu : mMenuList) menu->render(renderer);
    }
}
