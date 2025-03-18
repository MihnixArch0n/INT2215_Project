#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SDL.h>

#include "MyFont.hpp"
#include "MyTexture.hpp"
#include "GameSound.hpp"
#include "GameMusic.hpp"


class ResourceManager
{
public:
    bool loadResource(SDL_Renderer* renderer);

    [[nodiscard]] const MyTexture& getPaddleTexture() const {return mPaddleTexture;}
    [[nodiscard]] const MyTexture& getBallTexture() const {return mBallTexture;}
    [[nodiscard]] const MyTexture& getBrickTexture() const {return mBrickTexture;}
    [[nodiscard]] const MyTexture& getWonTexture() const {return mWonTexture;}
    [[nodiscard]] const MyTexture& getLostTexture() const {return mLostTexture;}
    [[nodiscard]] const MyFont& getFont() const {return mFont;}
    [[nodiscard]] const GameMusic& getMusic() const {return mMusic;}
    [[nodiscard]] const GameSound& getSound() const {return mSound;}
private:
    MyTexture mPaddleTexture;
    MyTexture mBallTexture;
    MyTexture mBrickTexture;
    MyTexture mWonTexture;
    MyTexture mLostTexture;

    MyFont mFont;

    GameSound mSound;
    GameMusic mMusic;
};


#endif //RESOURCEMANAGER_HPP
