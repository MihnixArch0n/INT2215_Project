#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP


#include <SDL.h>
#include <vector>
#include <memory>

#include "defs.hpp"
#include "menu/Menu.hpp"
#include "ResourceManager.hpp"


// TODO: Add Settings menu.

class MenuManager
{
public:
    bool init(ResourceManager& resourceManager, SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event, GameState& gameState);
    void update(GameState& gameState);
    void render(SDL_Renderer* renderer) const;
private:
    std::vector<std::unique_ptr<Menu>> mMenuList;
};



#endif //MENUMANAGER_HPP
