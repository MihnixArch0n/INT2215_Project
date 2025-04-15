#include "game_objects/GameObject.hpp"


void GameObject::render(SDL_Renderer *renderer) const
{
    SDL_Rect dst {mPosX, mPosY, mWidth, mHeight};
    mObjectTexture->render(renderer, &dst);
}

void GameObject::render(int x, int y, SDL_Renderer *renderer) const
{
    SDL_Rect dst {x, y, mWidth, mHeight};
    mObjectTexture->render(renderer, &dst);
}


double GameObject::getPosX() const {return mPosX;}
double GameObject::getPosY() const {return mPosY;}
int GameObject::getWidth() const {return mWidth;}
int GameObject::getHeight() const {return mHeight;}

void GameObject::setObjectTexture(const ResourceManager &manager)
{
    mObjectTexture = &manager.getTexture(getType(), getSubType());
}

void GameObject::setTexture(const ResourceManager &manager)
{
    mObjectTexture = manager.getObjectTexture(getType(), getSubType());
}


void GameObject::save(std::ofstream& saveFile) const
{
    saveFile << mPosX << " " << mPosY;
    saveFile << " " << mWidth << " " << mHeight;
}

void GameObject::load(std::ifstream& loadFile)
{
    loadFile >> mPosX >> mPosY;
    loadFile >> mWidth >> mHeight;
}
