#include "menu/EndMenu.hpp"

#include "button/QuitButton.hpp"
#include "button/PlayAgainButton.hpp"


bool EndMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    mButtonList.push_back(std::make_unique<QuitButton>());
    mButtonList.push_back(std::make_unique<PlayAgainButton>());
    return Menu::init(manager, renderer);
}

void EndMenu::handleEvents(SDL_Event &event, GameState& gameState)
{
    if (gameState == GameState::END) Menu::handleEvents(event, gameState);
}

void EndMenu::update(GameState &gameState)
{
    if (gameState == GameState::END)
    {
        hidden = false;
    }
    else hidden = true;
    Menu::update(gameState);
}
