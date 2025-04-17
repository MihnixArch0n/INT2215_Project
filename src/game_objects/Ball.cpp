#include <cmath>

#include "defs.hpp"
#include "my_utils.hpp"
#include "game_objects/Ball.hpp"
#include "game_objects/Brick.hpp"
#include "managers/AudioManager.hpp"

/**
 * Linear mapping to radian angle based on hit position.
*/
constexpr double HIT_POS_START = -(Paddle::PADDLE_WIDTH - Ball::BALL_WIDTH) / 2.0;
constexpr double HIT_POS_END = (Paddle::PADDLE_WIDTH - Ball::BALL_WIDTH) / 2.0;
constexpr double RAD_ANGLE_START = 3 * M_PI_4;
constexpr double RAD_ANGLE_END = M_PI_4;


Ball::Ball()
{
    // mPosX = mPosY = 0;
    mPosX = 0;
    mPosY = LEVEL_HEIGHT * 0.9;
    mWidth = BALL_WIDTH;
    mHeight = BALL_HEIGHT;
    mSubType = BallType::NORMAL;
}

Ball::Ball(const Ball& other)
{
    mPosX = other.mPosX;
    mPosY = other.mPosY;
    mWidth = BALL_WIDTH;
    mHeight = BALL_HEIGHT;

    mVelX = other.mVelX;
    mVelY = other.mVelY;

    mState = other.mState;
    mSubType = other.mSubType;
    mObjectTexture = other.mObjectTexture;
}

Ball::Ball(const Ball &other, double x, double y) : Ball(other)
{
    mPosX = x;
    mPosY = y;
}


void Ball::init(ResourceManager &manager)
{
    auto type = ObjectType::BALL;
    std::string resPath = "assets/img/balls";
    manager.addTexture(type, BallType::NORMAL, resPath + "/NormalBall.png");
    manager.addTexture(type, BallType::FIRE, resPath + "/FireBall.png");
}


void Ball::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        mState = BallState::MOVING;
        mVelX = 0;
        mVelY = -BALL_SPEED;
    }
}


void Ball::update(int deltaTime, const Paddle& paddle)
{
    if (mState == BallState::START)
    {
        mPosX = paddle.getPosX() + (paddle.getWidth() - mWidth) / 2.0;
        mPosY = paddle.getPosY() - mHeight;
    }
    else if (mState == BallState::MOVING)
    {
        mPosX += mVelX * my_utils::to_seconds(deltaTime);
        mPosY += mVelY * my_utils::to_seconds(deltaTime);
        bool collidedWithWall = false;

        if (mPosX < 0)
        {
            mPosX = 0;
            mVelX = -mVelX;
            collidedWithWall = true;
        }
        if (mPosX + mWidth > LEVEL_WIDTH)
        {
            mPosX = LEVEL_WIDTH - mWidth;
            mVelX = -mVelX;
            collidedWithWall = true;
        }
        if (mPosY < 0)
        {
            mPosY = 0;
            mVelY = -mVelY;
            collidedWithWall = true;
        }
        // if (mPosY + mHeight > LEVEL_HEIGHT)
        // {
        //     mPosY = LEVEL_HEIGHT - mHeight;
        //     mVelY = -mVelY;
        // }

        if (collidedWithWall) AudioManager::getInstance().getSound(SoundType::HIT)->play();

        if (mPosY > LEVEL_HEIGHT) mState = BallState::DEAD;
    }
}


void Ball::onCollision(GameObject& other, int deltaTime)
{
    double checkPosY = mPosY - mVelY * my_utils::to_seconds(deltaTime);
    double checkPosX = mPosX - mVelX * my_utils::to_seconds(deltaTime);

    if (other.getType() == ObjectType::PADDLE)
    {
        double ballCenterX = mPosX + mWidth / 2.0;
        double paddleCenterX = other.getPosX() + other.getWidth() / 2.0;

        if (checkPosY + mHeight < other.getPosY())
        {
            mPosY = other.getPosY() - mHeight;
            double angle = (ballCenterX - paddleCenterX - HIT_POS_START)
                / (HIT_POS_END - HIT_POS_START);
            angle = angle * (RAD_ANGLE_END - RAD_ANGLE_START) + RAD_ANGLE_START;
            mVelX = BALL_SPEED * cos(angle);
            mVelY = -BALL_SPEED * sin(angle);
        }
        else if (checkPosY > other.getPosY() + other.getHeight())
        {
            mPosY = other.getPosY() + other.getHeight();
            double angle = (ballCenterX - paddleCenterX - HIT_POS_START)
                / (HIT_POS_END - HIT_POS_START);
            angle = angle * (RAD_ANGLE_END - RAD_ANGLE_START) + RAD_ANGLE_START;
            mVelX = BALL_SPEED * cos(angle);
            mVelY = BALL_SPEED * sin(angle);
        }
        else if (checkPosX + mWidth < other.getPosX())
        {
            mPosX = other.getPosX() - mWidth;
            mVelX = -mVelX;
        }
        else
        {
            mPosX = other.getPosX() + other.getWidth();
            mVelX = -mVelX;
        }

        AudioManager::getInstance().getSound(SoundType::HIT)->play();
    }

    if (other.getType() == ObjectType::BRICK)
    {
        if (std::get<BallType>(mSubType) != BallType::FIRE)
        {
            if (checkPosY + mHeight < other.getPosY())
            {
                mPosY = other.getPosY() - mHeight;
                mVelY = -mVelY;
            }
            else if (checkPosY > other.getPosY() + other.getHeight())
            {
                mPosY = other.getPosY() + other.getHeight();
                mVelY = -mVelY;
            }
            else if (checkPosX + mWidth < other.getPosX())
            {
                mPosX = other.getPosX() - mWidth;
                mVelX = -mVelX;
            }
            else
            {
                mPosX = other.getPosX() + other.getWidth();
                mVelX = -mVelX;
            }
        }

        AudioManager::getInstance().getSound(SoundType::HIT)->play();
    }
}


BallState Ball::getState() const {return mState;}
void Ball::setState(BallState state) {mState = state;}

void Ball::save(std::ofstream &saveFile) const
{
    GameObject::save(saveFile);
    saveFile << " " << mVelX << " " << mVelY;
    saveFile << " " << static_cast<int>(std::get<BallType>(mSubType));
    saveFile << " " << static_cast<int>(mState);
    saveFile << std::endl;
}

void Ball::load(std::ifstream &loadFile)
{
    GameObject::load(loadFile);
    loadFile >> mVelX >> mVelY;
    int tmp;
    loadFile >> tmp;
    mSubType = static_cast<BallType>(tmp);
    loadFile >> tmp;
    mState = static_cast<BallState>(tmp);
}
