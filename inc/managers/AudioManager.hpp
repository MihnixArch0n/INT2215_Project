#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP


#include <map>

#include "defs.hpp"
#include "ResourceManager.hpp"
#include "game_resources/GameMusic.hpp"
#include "game_resources/GameSound.hpp"


class AudioManager
{
public:
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    static AudioManager& getInstance();
    void init(ResourceManager& manager);

    [[nodiscard]] const GameMusic& getMusic() const {return *gMusic;}
    [[nodiscard]] const GameSound* getSound(SoundType type) const;

    static void stopMusic() {GameMusic::stop();}

    static void updateMusicVolume();
    void updateSoundVolume() const;
private:
    AudioManager() = default;
    const GameMusic* gMusic = nullptr;
    std::map<SoundType, const GameSound*> gSoundMap;
};



#endif //AUDIOMANAGER_HPP
