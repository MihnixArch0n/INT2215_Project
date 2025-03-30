#include <iostream>
#include "button/Button.hpp"


bool Button::init(ResourceManager &resManager, SDL_Renderer* renderer)
{
    resManager.addText(mText, renderer);
    mTexture = resManager.getText(mText);
    if (mTexture == nullptr)
    {
        std::cerr << "Error: Could not load text resource" << std::endl;
        return false;
    }
    return true;
}

void Button::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, mBgColor->r, mBgColor->g, mBgColor->b, mBgColor->a);
    SDL_RenderFillRect(renderer, &mRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &mRect);
    mTexture->render(renderer, &mRect);
}

void Button::update(GameState& gameState)
{
    if (pressed)
    {
        mBgColor = &PRESSED_COLOR;
        onClick(gameState);
    }
    else if (hovered) mBgColor = &HOVERED_COLOR;
    else mBgColor = &NORMAL_COLOR;
}

void Button::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Point mousePos {x, y};
        if (SDL_PointInRect(&mousePos, &mRect)) hovered = true;
        else hovered = false;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (isHovered()) pressed = true;
    }
}

void Button::resetButtonState()
{
    hovered = false;
    pressed = false;
}
