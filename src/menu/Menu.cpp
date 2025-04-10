#include <iostream>
#include "menu/Menu.hpp"


bool Menu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    for (int i = 0; i < mButtonList.size(); ++i)
    {
        if (!mButtonList[i]->init(manager, renderer))
        {
            std::cerr << "Failed to initialize button list." << std::endl;
            return false;
        }
        mButtonList[i]->setPosY(i * (mButtonList[i]->getHeight() + PADDING));
    }
    return true;
}

void Menu::render(SDL_Renderer *renderer) const
{
    if (!hidden)
    {
        SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
        SDL_RenderFillRect(renderer, &mRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &mRect);

        for (auto &button : mButtonList) button->render(renderer);
    }
}

void Menu::handleEvents(SDL_Event &event, GameState& gameState)
{
    for (auto &button : mButtonList) button->handleEvent(event);
}

void Menu::update(GameState& gameState)
{
    if (!hidden)
        for (auto &button : mButtonList) button->update(gameState);
}

