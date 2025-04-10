#ifndef ENDMENU_HPP
#define ENDMENU_HPP


#include "menu/Menu.hpp"


class EndMenu : public Menu
{
public:
    bool init(ResourceManager &manager, SDL_Renderer *renderer) override;
    void handleEvents(SDL_Event &event, GameState& gameState) override;
    void update(GameState &gameState) override;
};



#endif //ENDMENU_HPP
