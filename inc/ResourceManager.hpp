#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SDL.h>
#include <vector>

#include "defs.hpp"
#include "MyFont.hpp"
#include "MyTexture.hpp"
#include "GameSound.hpp"
#include "GameMusic.hpp"


class ResourceManager
{
public:
    bool loadResource(SDL_Renderer* renderer);

    [[nodiscard]] const MyTexture& getWonTexture() const {return mWonTexture;}
    [[nodiscard]] const MyTexture& getLostTexture() const {return mLostTexture;}
    [[nodiscard]] const MyFont& getFont() const {return mFont;}
    [[nodiscard]] const GameMusic& getMusic() const {return mMusic;}
    [[nodiscard]] const GameSound& getSound() const {return mSound;}
    [[nodiscard]] const MyTexture& getTexture(ObjectType type, ObjectSubType subType) const;
private:
    std::vector<std::vector<MyTexture>> mTextureList;
    MyTexture mWonTexture;
    MyTexture mLostTexture;

    MyFont mFont;

    GameSound mSound;
    GameMusic mMusic;
};


#endif //RESOURCEMANAGER_HPP
