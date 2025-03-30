#include "managers/CollisionManager.hpp"


void CollisionManager::handleCollision(GameObject& obj1, GameObject& obj2, int deltaTime)
{
    if (checkCollision(obj1, obj2))
    {
        obj1.onCollision(obj2, deltaTime);
        obj2.onCollision(obj1, deltaTime);
    }
}

bool CollisionManager::checkCollision(const GameObject& obj1, const GameObject& obj2)
{
    if (obj1.getPosX() + obj1.getWidth() <= obj2.getPosX()) return false;
    if (obj1.getPosX() >= obj2.getPosX() + obj2.getWidth()) return false;
    if (obj1.getPosY() + obj1.getHeight() <= obj2.getPosY()) return false;
    if (obj1.getPosY() >= obj2.getPosY() + obj2.getHeight()) return false;
    return true;
}
