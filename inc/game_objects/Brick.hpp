#ifndef BRICK_HPP
#define BRICK_HPP


#include "game_objects/GameObject.hpp"

class Ball;

class Brick : public GameObject
{
public:
    Brick();
    Brick(int x, int y, BrickType type = BrickType::EASY);
    explicit Brick(BrickType type) {mSubType = type;}
    ~Brick() override = default;

    void init(ResourceManager &manager) override;

    void setObjectTexture(const ResourceManager &manager) override;

    [[nodiscard]] bool isAlive() const {return lives > 0;}

    void update(int deltaTime, const ResourceManager& manager);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::BRICK;}
    void onCollision(GameObject &other, int deltaTime) override;

    void save(std::ofstream &saveFile) const override;
    void load(std::ifstream &loadFile) override;

    constexpr static int BRICK_WIDTH = 70;
    constexpr static int BRICK_HEIGHT = 33;
    constexpr static int COLLISION_COOLDOWN = 200;
private:
    bool alive = true;
    int lives = 1;
    int timeSinceLastCooldown = 0;
};


#endif //BRICK_HPP
