#include "GameObject.hpp"

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

bool GameObject::isCollidedWithOther(const GameObject& other) const
{
    if (mPosX + mWidth < other.mPosX) return false;
    if (mPosX > other.mPosX + other.mWidth) return false;
    if (mPosY + mHeight < other.mPosY) return false;
    if (mPosY > other.mPosY + other.mHeight) return false;
    return true;
}

MyTexture* GameObject::getObjectTexture() const {return mObjectTexture;}
void GameObject::setObjectTexture(MyTexture* texture) {mObjectTexture = texture;}
int GameObject::getPosX() const {return mPosX;}
int GameObject::getPosY() const {return mPosY;}
int GameObject::getWidth() const {return mWidth;}
int GameObject::getHeight() const {return mHeight;}