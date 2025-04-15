#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL.h>
#include <fstream>
#include <managers/ResourceManager.hpp>

#include "game_resources/MyTexture.hpp"
#include "defs.hpp"


class GameObject
{
public:
    GameObject() = default;
    GameObject(double x, double y) : mPosX(x), mPosY(y) {}
    virtual ~GameObject() = default;

    void render(SDL_Renderer* renderer) const;
    void render(int x, int y, SDL_Renderer* renderer) const;

    virtual void setObjectTexture(const ResourceManager& manager);
    void setTexture(const ResourceManager& manager);

    [[nodiscard]] double getPosX() const;
    [[nodiscard]] double getPosY() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] virtual ObjectType getType() const = 0;
    [[nodiscard]] ObjectSubType getSubType() const {return mSubType;}

    void setPosX(double mPosX) {this->mPosX = mPosX;}
    void setPosY(double mPosY) {this->mPosY = mPosY;}

    void setSubType(ObjectSubType subType) {mSubType = subType;}

    virtual void onCollision(GameObject& other, int deltaTime) = 0;

    virtual void save(std::ofstream& saveFile) const;
    virtual void load(std::ifstream& loadFile);
protected:
    double mPosX = 0, mPosY = 0;
    int mWidth = 0, mHeight = 0;
    ObjectSubType mSubType;
    const MyTexture* mObjectTexture = nullptr;
};


#endif //GAMEOBJECT_HPP
