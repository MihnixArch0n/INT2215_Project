#ifndef STARTMENU_HPP
#define STARTMENU_HPP


#include <functional>
#include "menu/Menu.hpp"


class StartMenu : public Menu
{
public:
    explicit StartMenu(std::function<void()> callback);
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    void handleEvents(SDL_Event &event, GameState& gameState) override;
    void update(GameState &gameState) override;
private:
    std::function<void()> setSettingGroup;
};


#endif //STARTMENU_HPP
