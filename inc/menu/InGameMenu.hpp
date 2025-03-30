#ifndef INGAMEMENU_HPP
#define INGAMEMENU_HPP


#include "Menu.hpp"


class InGameMenu : public Menu
{
public:
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    void handleEvents(SDL_Event &event, GameState& gameState) override;
    void update(GameState &gameState) override;
};


#endif //INGAMEMENU_HPP
