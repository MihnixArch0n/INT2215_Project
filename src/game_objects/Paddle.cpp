#include "defs.hpp"
#include "my_utils.hpp"
#include "game_objects/Paddle.hpp"


Paddle::Paddle()
{
    mPosX = 300;
    mPosY = LEVEL_HEIGHT * 0.9;
    mWidth = PADDLE_WIDTH;
    mHeight = PADDLE_HEIGHT;

    mSubType = PaddleType::NORMAL;
}

void Paddle::init(ResourceManager &manager)
{
    auto type = ObjectType::PADDLE;
    std::string resPath = "assets/img/paddles/Paddle.png";

    manager.addTexture(type, PaddleType::NORMAL, resPath);
}

void Paddle::handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                mVel -= PADDLE_SPEED;
                break;
            case SDLK_RIGHT:
                mVel += PADDLE_SPEED;
                break;
            default: break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                mVel += PADDLE_SPEED;
            break;
            case SDLK_RIGHT:
                mVel -= PADDLE_SPEED;
            break;
            default: break;
        }
    }
}

void Paddle::update(int deltaTime)
{
    mPosX += mVel * my_utils::to_seconds(deltaTime);
    if (mPosX < 0) mPosX = 0;
    if (mPosX + mWidth > LEVEL_WIDTH) mPosX = LEVEL_WIDTH - mWidth;
}

void Paddle::save(std::ofstream &saveFile) const
{
    GameObject::save(saveFile);
    saveFile << std::endl;
}
