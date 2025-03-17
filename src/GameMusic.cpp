#include <iostream>

#include "GameMusic.hpp"


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
    Mix_PlayMusic(mMusic, -1);
}

void GameMusic::stop() const
{
    Mix_HaltMusic();
}

void GameMusic::pause() const
{
    Mix_PauseMusic();
}

void GameMusic::resume() const
{
    Mix_ResumeMusic();
}