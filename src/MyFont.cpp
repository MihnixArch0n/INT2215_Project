#include "MyFont.hpp"

#include <iostream>
#include <ostream>


MyFont::~MyFont()
{
    free();
}

void MyFont::free()
{
    TTF_CloseFont(mFont);
    mFont = nullptr;
}

bool MyFont::loadFont(const char* fontPath, int fontSize)
{
    free();

    mFont = TTF_OpenFont(fontPath, fontSize);
    if (mFont == nullptr)
    {
        std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

TTF_Font* MyFont::getFont() const {return mFont;}