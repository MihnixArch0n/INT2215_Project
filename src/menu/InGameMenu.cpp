#include "menu/InGameMenu.hpp"

#include "button/ResumeButton.hpp"
#include "button/SettingsButton.hpp"
#include "button/QuitButton.hpp"


bool InGameMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    mButtonList.push_back(std::make_unique<ResumeButton>());
    mButtonList.push_back(std::make_unique<SettingsButton>());
    mButtonList.push_back(std::make_unique<QuitButton>());
    return Menu::init(manager, renderer);
}

void InGameMenu::handleEvents(SDL_Event &event, GameState& gameState)
{
    if (gameState == GameState::PLAYING || gameState == GameState::PAUSED)
    {
        Menu::handleEvents(event, gameState);
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            if (gameState == GameState::PLAYING) gameState = GameState::PAUSED;
            else gameState = GameState::PLAYING;
        }
    }
}

void InGameMenu::update(GameState &gameState)
{
    if (gameState == GameState::PAUSED)
    {
        hidden = false;
    }
    else hidden = true;
    Menu::update(gameState);
}