#include "managers/AudioManager.hpp"
#include "managers/ConfigManager.hpp"


void AudioManager::init(ResourceManager& manager)
{
    manager.addSound(SoundType::HIT, "assets/audio/sound/hit02.mp3.flac");
    manager.addSound(SoundType::COLLECT, "assets/audio/sound/game-bonus-2-294436.mp3");

    gMusic = &manager.getMusic();
    gSoundMap[SoundType::HIT] = manager.getSound(SoundType::HIT);
    gSoundMap[SoundType::COLLECT] = manager.getSound(SoundType::COLLECT);

    updateMusicVolume();
    updateSoundVolume();
}

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

void AudioManager::updateMusicVolume()
{
    int newVol = ConfigManager::getInstance().getMusicVolume();
    newVol = static_cast<int>((newVol * 10.0 / 100) * MIX_MAX_VOLUME);
    Mix_VolumeMusic(newVol);
}

void AudioManager::updateSoundVolume() const
{
    int newVol = ConfigManager::getInstance().getSoundVolume();
    newVol = static_cast<int>((newVol * 10.0 / 100) * MIX_MAX_VOLUME);
    for (const auto &pair : gSoundMap) Mix_VolumeChunk(pair.second->getSound(), newVol);
}

const GameSound* AudioManager::getSound(SoundType type) const
{
    auto it = gSoundMap.find(type);
    if (it == gSoundMap.end()) return nullptr;
    return it->second;
}
