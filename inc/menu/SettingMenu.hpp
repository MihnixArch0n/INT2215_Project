#ifndef SETTINGMENU_HPP
#define SETTINGMENU_HPP


#include <functional>
#include "menu/Menu.hpp"


class SettingMenu : public Menu
{
public:
    explicit SettingMenu(std::function<void()> callback);
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    // void handleEvents(SDL_Event &event, GameState &gameState) override;
    // void update(GameState &gameState) override;

private:
    std::function<void()> setNormalGroup;
};
#endif //SETTINGMENU_HPP
