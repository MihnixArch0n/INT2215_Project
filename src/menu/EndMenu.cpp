#include "menu/EndMenu.hpp"

#include "button/QuitButton.hpp"


bool EndMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    // TODO: Add play again button.
    mButtonList.push_back(std::make_unique<QuitButton>());
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
