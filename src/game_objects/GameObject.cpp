#include "game_objects/GameObject.hpp"

GameObject::~GameObject() = default;


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