#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL.h>
#include "MyTexture.hpp"

class GameObject
{
public:
    virtual ~GameObject() = 0;
    void render(SDL_Renderer* renderer) const;
    void render(int x, int y, SDL_Renderer* renderer) const;

    [[nodiscard]] MyTexture* getObjectTexture() const;
    void setObjectTexture(MyTexture* texture);

    [[nodiscard]] bool isCollidedWithOther(const GameObject& other) const;
    [[nodiscard]] int getPosX() const;
    [[nodiscard]] int getPosY() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
protected:
    int mPosX = 0, mPosY = 0;
    int mWidth = 0, mHeight = 0;
    MyTexture* mObjectTexture = nullptr;
};


#endif //GAMEOBJECT_HPP
