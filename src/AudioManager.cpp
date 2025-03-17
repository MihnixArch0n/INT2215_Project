#include "AudioManager.hpp"

void AudioManager::init(GameMusic* music, GameSound* sound)
{
    gMusic = music;
    gSound = sound;
}

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}
