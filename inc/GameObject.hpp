#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL.h>
#include "MyTexture.hpp"


enum class ObjectType
{
    BALL,
    PADDLE,
    BRICK
};


class GameObject
{
public:
    virtual ~GameObject() = 0;
    void render(SDL_Renderer* renderer) const;
    void render(int x, int y, SDL_Renderer* renderer) const;

    void setObjectTexture(const MyTexture& texture) {mObjectTexture = &texture;}

    [[nodiscard]] double getPosX() const;
    [[nodiscard]] double getPosY() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] virtual ObjectType getType() const = 0;

    virtual void onCollision(GameObject& other, int deltaTime) = 0;
protected:
    double mPosX = 0, mPosY = 0;
    int mWidth = 0, mHeight = 0;
    const MyTexture* mObjectTexture = nullptr;
};


#endif //GAMEOBJECT_HPP
