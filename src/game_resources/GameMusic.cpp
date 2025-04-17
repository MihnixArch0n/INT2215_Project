#include <iostream>

#include "game_resources/GameMusic.hpp"
#include "managers/ConfigManager.hpp"


GameMusic::~GameMusic()
{
    free();
}

void GameMusic::free()
{
    Mix_FreeMusic(mMusic);
    mMusic = nullptr;
}

bool GameMusic::loadMusic(const char* filePath)
{
    free();

    mMusic = Mix_LoadMUS(filePath);
    if (mMusic == nullptr)
    {
        std::cerr << "Error loading music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameMusic::play() const
{
    if (!Mix_PlayingMusic() && ConfigManager::getInstance().getMusicStatus()) Mix_PlayMusic(mMusic, -1);
}

void GameMusic::stop()
{
    Mix_HaltMusic();
}

void GameMusic::pause()
{
    Mix_PauseMusic();
}

void GameMusic::resume()
{
    Mix_ResumeMusic();
}