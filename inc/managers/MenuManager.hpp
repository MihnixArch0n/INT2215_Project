#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP


#include <SDL.h>
#include <vector>
#include <memory>

#include "defs.hpp"
#include "menu/Menu.hpp"
#include "managers/ResourceManager.hpp"
#include "menu/SettingMenu.hpp"


class MenuManager
{
public:
    bool init(ResourceManager& resourceManager, SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event, GameState& gameState);
    void update(GameState& gameState);
    void render(SDL_Renderer* renderer) const;
private:
    std::vector<std::unique_ptr<Menu>> mMenuList;
    std::unique_ptr<Menu> mSettingMenu;

    MenuGroupType mMenuGroup = MenuGroupType::NORMAL;

    std::function<void()> setNormalGroup = [this]() {
        this->mMenuGroup = MenuGroupType::NORMAL;
    };

    std::function<void()> setSettingGroup = [this]() {
        this->mMenuGroup = MenuGroupType::SETTINGS;
    };
};


#endif //MENUMANAGER_HPP
