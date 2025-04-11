#ifndef POWERUPDROP_HPP
#define POWERUPDROP_HPP


#include "defs.hpp"
#include "game_objects/GameObject.hpp"


class PowerUpDrop : public GameObject
{
public:
    PowerUpDrop();
    ~PowerUpDrop() override = default;

    void update(int deltaTime);
    void onCollision(GameObject &other, int deltaTime) override;

    [[nodiscard]] ObjectType getType() const override {return ObjectType::POWER_UP_DROP;}

    [[nodiscard]] PowerUpDropStatus getStatus() const {return mStatus;}

    void save(std::ofstream &saveFile) const override;
    void load(std::ifstream &loadFile) override;

    constexpr static int DROP_SPEED = 100;
    constexpr static int WIDTH = 32;
    constexpr static int HEIGHT = 32;
private:
    PowerUpDropStatus mStatus = PowerUpDropStatus::ALIVE;
    double mVel = DROP_SPEED;
};


#endif //POWERUPDROP_HPP
