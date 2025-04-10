#include "game_resources/GameSound.hpp"

#include <iostream>
#include "managers/ConfigManager.hpp"

GameSound::~GameSound()
{
    free();
}

void GameSound::free()
{
    Mix_FreeChunk(mSound);
    mSound = nullptr;
}

bool GameSound::loadSound(const char *filePath)
{
    free();

    mSound = Mix_LoadWAV(filePath);
    if (mSound == nullptr)
    {
        std::cerr << "Error loading sound: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameSound::play() const
{
    if (ConfigManager::getInstance().getSoundStatus())
        Mix_PlayChannel(-1, mSound, 0);
}