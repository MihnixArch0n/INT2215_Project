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

    static void init(ResourceManager &manager);

    [[nodiscard]] bool isAlive() const {return lives > 0;}

    void update(int deltaTime, const ResourceManager& manager);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::BRICK;}
    void onCollision(GameObject &other, int deltaTime) override;

    void save(std::ofstream &saveFile) const override;
    void load(std::ifstream &loadFile) override;

    constexpr static int BRICK_WIDTH = 70;
    constexpr static int BRICK_HEIGHT = 33;
    constexpr static int COLLISION_COOLDOWN = 160;
private:
    int lives = 1;
    int timeSinceLastCooldown = 0;

    std::vector<double> probabilities {0.5, 0.3, 0.2};
};


#endif //BRICK_HPP
