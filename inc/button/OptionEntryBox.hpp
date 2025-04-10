#ifndef OPTIONENTRYBOX_HPP
#define OPTIONENTRYBOX_HPP


#include <string>
#include <vector>
#include "defs.hpp"
#include "managers/ResourceManager.hpp"
#include "button/OptionEntryButton.hpp"


class OptionEntryBox
{
public:
    explicit OptionEntryBox(SettingType type);
    bool init(ResourceManager& resManager, SDL_Renderer* renderer);
    void handleEvent(SDL_Event &event);
    void update();
    void render(SDL_Renderer* renderer);

    void setPosX(int posX) {mRect.x = posX;}
    void setPosY(int posY) {mRect.y = posY;}
    int getWidth() {return mRect.w;}
    int getHeight() {return mRect.h;}
private:
    SDL_Rect mRect {0, 0, 200, 40};
    std::string mName;
    const MyTexture* mNameTexture = nullptr;
    OptionEntryButton mLeftButton;
    OptionEntryButton mRightButton;
    std::vector<std::string> mOptions;
    std::vector<const MyTexture*> mOptionsTextures;
    int mSelectedOption = 0;
    SettingType mType;
};


#endif //OPTIONENTRYBOX_HPP
