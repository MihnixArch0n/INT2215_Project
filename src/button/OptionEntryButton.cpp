#include "button/OptionEntryButton.hpp"


OptionEntryButton::OptionEntryButton(ButtonType type)
{
    mType = type;
}

bool OptionEntryButton::init(ResourceManager &resManager, SDL_Renderer *renderer)
{
    mTexture = resManager.getTexture(mType);
    return true;
}


void OptionEntryButton::onClick(GameState &gameState)
{

}

ButtonType OptionEntryButton::getType() const
{
    return mType;
}