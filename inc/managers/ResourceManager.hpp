#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SDL.h>
#include <vector>
#include <string>
#include <map>
#include <set>

#include "defs.hpp"
#include "game_resources/MyFont.hpp"
#include "game_resources/MyTexture.hpp"
#include "game_resources/GameSound.hpp"
#include "game_resources/GameMusic.hpp"


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
    void addText(const std::string& text, SDL_Renderer *renderer);
    [[nodiscard]] const MyTexture* getText(const std::string& text) const;
    std::vector<std::vector<MyTexture>> mTextureList;
    MyTexture mWonTexture;
    MyTexture mLostTexture;
    std::set<std::string> mTextList;
    std::map<std::string, MyTexture> mTextTextureList;
    MyFont mFont;

    GameSound mSound;
    GameMusic mMusic;
};


#endif //RESOURCEMANAGER_HPP
