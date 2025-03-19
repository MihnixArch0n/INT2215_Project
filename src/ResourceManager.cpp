#include <iostream>
#include <map>

#include "ResourceManager.hpp"
#include "GameObject.hpp"


bool ResourceManager::loadResource(SDL_Renderer* renderer)
{
    bool success = true;
    int objNums = static_cast<int>(ObjectType::TOTAL);
    mTextureList.resize(objNums);
    std::map<int, int> objMap =
    {
        {static_cast<int>(ObjectType::PADDLE), static_cast<int>(PaddleType::TOTAL)},
        {static_cast<int>(ObjectType::BALL), static_cast<int>(BallType::TOTAL)},
        {static_cast<int>(ObjectType::BRICK), static_cast<int>(BrickType::TOTAL)}
    };
    std::map<int, std::string> objName =
    {
        {static_cast<int>(ObjectType::PADDLE), "paddles/Paddle_"},
        {static_cast<int>(ObjectType::BALL), "balls/Ball_"},
        {static_cast<int>(ObjectType::BRICK), "bricks/Brick_"}
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
                std::cerr << "Failed to load paddle texture" << std::endl;
                return false;
            }
        }
    }

    if (mFont.loadFont("res/fonts/GohuFont14NerdFontMono-Regular.ttf", 42))
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
    return success;
}

const MyTexture& ResourceManager::getTexture(ObjectType type, SubType subType) const
{
    int typeInt = static_cast<int>(type);
    int subTypeInt = -1;
    if (type == ObjectType::BALL && std::holds_alternative<BallType>(subType))
        subTypeInt = static_cast<int>(std::get<BallType>(subType));
    else if (type == ObjectType::PADDLE && std::holds_alternative<PaddleType>(subType))
        subTypeInt = static_cast<int>(std::get<PaddleType>(subType));
    else if (type == ObjectType::BRICK && std::holds_alternative<BrickType>(subType))
        subTypeInt = static_cast<int>(std::get<BrickType>(subType));
    return mTextureList[typeInt][subTypeInt];
}
