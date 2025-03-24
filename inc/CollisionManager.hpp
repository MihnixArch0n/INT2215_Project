#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include "GameObject.hpp"

class CollisionManager
{
public:
    CollisionManager() = delete;
    ~CollisionManager() = delete;

    static void handleCollision(GameObject& obj1, GameObject& obj2, int deltaTime);
    static bool checkCollision(const GameObject& obj1, const GameObject& obj2);
private:
};



#endif //COLLISIONMANAGER_HPP
