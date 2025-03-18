#include "AudioManager.hpp"

void AudioManager::init(const GameMusic& music, const GameSound& sound)
{
    gMusic = &music;
    gSound = &sound;
}

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}
