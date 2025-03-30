#ifndef MYFONT_HPP
#define MYFONT_HPP


#include <SDL_ttf.h>


class MyFont
{
public:
    ~MyFont();

    bool loadFont(const char* fontPath, int fontSize);

    void free();

    [[nodiscard]] TTF_Font* getFont() const;
private:
    TTF_Font* mFont = nullptr;
};



#endif //MYFONT_HPP
