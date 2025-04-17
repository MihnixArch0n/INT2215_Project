#ifndef BRICK_HPP
#define BRICK_HPP


#include "game_objects/GameObject.hpp"


class Brick : public GameObject
{
public:
    Brick();
    ~Brick() override = default;

    static void init(ResourceManager &manager);

    [[nodiscard]] bool isAlive() const {return lives > 0;}

    void update(int deltaTime, const ResourceManager& manager);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::BRICK;}
    void onCollision(GameObject &other, int deltaTime) override;

    [[nodiscard]] bool hasDrop() const {return drop;}

    void save(std::ofstream &saveFile) const override;
    void load(std::ifstream &loadFile) override;

    constexpr static int BRICK_WIDTH = 70;
    constexpr static int BRICK_HEIGHT = 33;
    constexpr static int COLLISION_COOLDOWN = 160;
private:
    int lives = 1;
    int timeSinceLastCooldown = 0;
    bool drop;
};


#endif //BRICK_HPP
