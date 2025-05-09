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
    void addSound(SoundType soundType, const std::string& filePath);
    [[nodiscard]] const GameSound* getSound(SoundType type) const;

    [[nodiscard]] const MyTexture* getTexture(ButtonType type) const;

    void addTexture(ObjectType type, ObjectSubType subType, const std::string& filePath);
    [[nodiscard]] const MyTexture* getObjectTexture(ObjectType type, ObjectSubType subType) const;

    void addText(const std::string& text, SDL_Renderer *renderer);
    [[nodiscard]] const MyTexture* getText(const std::string& text) const;

private:
    MyTexture mWonTexture;
    MyTexture mLostTexture;
    std::map<std::string, MyTexture> mTextTextureList;
    MyFont mFont;

    std::map<SoundType, GameSound> mSoundList;
    GameMusic mMusic;

    std::map<ButtonType, MyTexture> mButtonTextures;
    std::map<ObjectType, std::map<ObjectSubType, MyTexture>> mObjectTextures;
    SDL_Renderer* pRenderer = nullptr;
};


#endif //RESOURCEMANAGER_HPP
