#ifndef GAMESOUND_HPP
#define GAMESOUND_HPP


#include <SDL_mixer.h>


class GameSound
{
public:
    ~GameSound();

    void free();
    bool loadSound(const char* filePath);

    void play() const;
private:
    Mix_Chunk* mSound = nullptr;
};


#endif //GAMESOUND_HPP
