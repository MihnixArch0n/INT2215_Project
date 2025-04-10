#include "managers/AudioManager.hpp"

#include "managers/ConfigManager.hpp"

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

void AudioManager::updateMusicVolume()
{
    int newVol = ConfigManager::getInstance().getMusicVolume();
    newVol = (newVol * 10.0 / 100) * MIX_MAX_VOLUME;
    Mix_VolumeMusic(newVol);
}

void AudioManager::updateSoundVolume()
{
    int newVol = ConfigManager::getInstance().getSoundVolume();
    newVol = (newVol * 10.0 / 100) * MIX_MAX_VOLUME;
    Mix_VolumeChunk(gSound->getSound(), newVol);
}