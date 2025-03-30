#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP


#include "game_resources/GameMusic.hpp"
#include "game_resources/GameSound.hpp"


class AudioManager
{
public:
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    static AudioManager& getInstance();
    void init(const GameMusic& music, const GameSound& sound);

    [[nodiscard]] const GameMusic& getMusic() const {return *gMusic;}
    [[nodiscard]] const GameSound& getSound() const {return *gSound;}
private:
    AudioManager() = default;
    const GameMusic* gMusic = nullptr;
    const GameSound* gSound = nullptr;
};



#endif //AUDIOMANAGER_HPP
