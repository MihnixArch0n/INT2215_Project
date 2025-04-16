#include <iostream>
#include <map>

#include "managers/ResourceManager.hpp"
#include "game_objects/GameObject.hpp"


bool ResourceManager::loadResource(SDL_Renderer* renderer)
{
    pRenderer = renderer;
    bool success = true;
    mTextureList.resize(static_cast<int>(ObjectType::TOTAL));
    std::map<int, int> objMap =
    {
        {static_cast<int>(ObjectType::POWER_UP_DROP), static_cast<int>(PowerUpDropType::TOTAL)}
    };
    std::map<int, std::string> objName =
    {
        {static_cast<int>(ObjectType::POWER_UP_DROP), "power_ups/PowerUp_"}
    };

    std::string textureDir = "assets/img/";
    for (const auto &p : objMap)
    {
        mTextureList[p.first].resize(p.second);
        for (int i = 0; i < (p.second); ++i)
        {
            std::string filePath = textureDir + objName[p.first];
            filePath += std::to_string(i+1) + ".png";
            if (!mTextureList[p.first][i].loadFromFile(renderer, filePath.c_str()))
            {
                std::cerr << "Failed to load texture" << std::endl;
                return false;
            }
        }
    }

    if (mFont.loadFont("res/fonts/GohuFont14NerdFontMono-Regular.ttf", 36))
    {
        if (!mWonTexture.loadFromRenderedText("You won", mFont, renderer))
        {
            std::cerr << "Failed to load won texture" << std::endl;
            success = false;
        }
        if (!mLostTexture.loadFromRenderedText("You lost", mFont, renderer))
        {
            std::cerr << "Failed to load lost texture" << std::endl;
            success = false;
        }
    }
    else
    {
        std::cerr << "Failed to load font " << std::endl;
        success = false;
    }

    if (!mSound.loadSound("assets/audio/sound/hit02.mp3.flac"))
    {
        std::cerr << "Failed to load sound" << std::endl;
        success = false;
    }
    if (!mMusic.loadMusic("assets/audio/music/best-game-console-301284.mp3"))
    {
        std::cerr << "Failed to load music" << std::endl;
        success = false;
    }

    if (!mButtonTextures[ButtonType::OPTION_ENTRY_LEFT].loadFromFile(renderer,
        "assets/img/button/LefttOption.png")
        || !mButtonTextures[ButtonType::OPTION_ENTRY_RIGHT].loadFromFile(renderer,
            "assets/img/button/RightOption.png"))
    {
        std::cerr << "Failed to load button" << std::endl;
        success = false;
    }
    return success;
}

const MyTexture& ResourceManager::getTexture(ObjectType type, ObjectSubType subType) const
{
    int typeInt = static_cast<int>(type);
    int subTypeInt = -1;
    if (type == ObjectType::BALL && std::holds_alternative<BallType>(subType))
        subTypeInt = static_cast<int>(std::get<BallType>(subType));
    else if (type == ObjectType::PADDLE && std::holds_alternative<PaddleType>(subType))
        subTypeInt = static_cast<int>(std::get<PaddleType>(subType));
    else if (type == ObjectType::BRICK && std::holds_alternative<BrickType>(subType))
        subTypeInt = static_cast<int>(std::get<BrickType>(subType));
    else if (type == ObjectType::POWER_UP_DROP && std::holds_alternative<PowerUpDropType>(subType))
        subTypeInt = static_cast<int>(std::get<PowerUpDropType>(subType));
    return mTextureList[typeInt][subTypeInt];
}

const MyTexture* ResourceManager::getTexture(ButtonType type) const
{
    auto it = mButtonTextures.find(type);
    if (it == mButtonTextures.end()) return nullptr;
    return &(it->second);
}

void ResourceManager::addText(const std::string &text, SDL_Renderer *renderer)
{
    mTextList.insert(text);
    mTextTextureList.emplace(text, MyTexture());
    mTextTextureList[text].loadFromRenderedText(text.c_str(), mFont, renderer);
}

const MyTexture* ResourceManager::getText(const std::string &text) const
{
    auto it = mTextTextureList.find(text);
    if (it == mTextTextureList.end()) return nullptr;
    return &(it->second);
}

void ResourceManager::addTexture(ObjectType type, ObjectSubType subType, const std::string &filePath)
{
    if (mObjectTextures[type].find(subType) == mObjectTextures[type].end())
    {
        bool tmp = !mObjectTextures[type][subType].loadFromFile(pRenderer, filePath.c_str());
        if (tmp) std::cerr << "Failed to load " << filePath << std::endl;
    }
}

const MyTexture* ResourceManager::getObjectTexture(ObjectType type, ObjectSubType subType) const
{
    auto it1 = mObjectTextures.find(type);
    if (it1 == mObjectTextures.end()) return nullptr;

    auto it2 = it1->second.find(subType);
    if (it2 == it1->second.end()) return nullptr;
    return &(it2->second);
}
