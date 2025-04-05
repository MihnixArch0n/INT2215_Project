#include "menu/SettingMenu.hpp"

#include "button/SettingsButton.hpp"
#include "button/BackButton.hpp"


SettingMenu::SettingMenu(std::function<void()> callback) : setNormalGroup(callback) {}

bool SettingMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    mButtonList.push_back(std::make_unique<BackButton>(setNormalGroup));
    Menu::init(manager, renderer);
    return true;
}

