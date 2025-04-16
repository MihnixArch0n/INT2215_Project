#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>

#include "game_objects/GameObject.hpp"


class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle() override = default;

    static void init(ResourceManager& manager);

    void handleEvent(const SDL_Event& e);
    void update(int deltaTime);

    [[nodiscard]] ObjectType getType() const override {return ObjectType::PADDLE;}
    void onCollision(GameObject &other, int deltaTime) override {}

    void save(std::ofstream &saveFile) const override;

    constexpr static int PADDLE_WIDTH = 120;
    constexpr static int PADDLE_HEIGHT = 30;
    constexpr static int PADDLE_SPEED = 450;
private:
    double mVel = 0;
};

#endif //PADDLE_HPP
