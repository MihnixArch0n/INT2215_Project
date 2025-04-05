#ifndef INGAMEMENU_HPP
#define INGAMEMENU_HPP


#include <functional>

#include "menu/Menu.hpp"


class InGameMenu : public Menu
{
public:
    explicit InGameMenu(std::function<void()> callback);
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    void handleEvents(SDL_Event &event, GameState& gameState) override;
    void update(GameState &gameState) override;
private:
    std::function<void()> setSettingGroup;
};


#endif //INGAMEMENU_HPP
