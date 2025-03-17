#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP


#include "GameMusic.hpp"
#include "GameSound.hpp"


class AudioManager
{
public:
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    static AudioManager& getInstance();
    void init(GameMusic* music, GameSound* sound);

    [[nodiscard]] const GameMusic& getMusic() const {return *gMusic;}
    [[nodiscard]] const GameSound& getSound() const {return *gSound;}
private:
    AudioManager() = default;
    GameMusic* gMusic = nullptr;
    GameSound* gSound = nullptr;
};



#endif //AUDIOMANAGER_HPP
