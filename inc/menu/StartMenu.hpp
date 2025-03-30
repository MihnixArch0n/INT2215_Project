#ifndef STARTMENU_HPP
#define STARTMENU_HPP


#include "menu/Menu.hpp"


class StartMenu : public Menu
{
public:
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    void handleEvents(SDL_Event &event, GameState& gameState) override;
    void update(GameState &gameState) override;
};


#endif //STARTMENU_HPP
