#ifndef GAMEMUSIC_HPP
#define GAMEMUSIC_HPP


#include <SDL_mixer.h>


class GameMusic
{
public:
    ~GameMusic();

    void free();
    bool loadMusic(const char* filePath);

    void play() const;
    void stop() const;
    void pause() const;
    void resume() const;
private:
    Mix_Music* mMusic = nullptr;
};



#endif //GAMEMUSIC_HPP
