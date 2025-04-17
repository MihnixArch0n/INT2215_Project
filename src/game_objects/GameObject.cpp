#include "game_objects/GameObject.hpp"


void GameObject::render(SDL_Renderer *renderer) const
{
    SDL_Rect dst {static_cast<int>(mPosX), static_cast<int>(mPosY), mWidth, mHeight};
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
