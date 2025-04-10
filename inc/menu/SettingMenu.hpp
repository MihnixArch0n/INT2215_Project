#ifndef SETTINGMENU_HPP
#define SETTINGMENU_HPP


#include <functional>
#include "menu/Menu.hpp"
#include "button/OptionEntryBox.hpp"


class SettingMenu : public Menu
{
public:
    explicit SettingMenu(std::function<void()> callback);
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    void handleEvents(SDL_Event &event, GameState &gameState) override;
    void update(GameState &gameState) override;
    void render(SDL_Renderer *renderer) const override;
private:
    std::function<void()> setNormalGroup;
    std::vector<OptionEntryBox> mOptionEntries;
};
#endif //SETTINGMENU_HPP
