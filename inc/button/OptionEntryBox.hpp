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
    void render(SDL_Renderer* renderer) const;

    void setPosX(int posX) {mRect.x = posX;}
    void setPosY(int posY) {mRect.y = posY;}
    [[nodiscard]] int getWidth() const {return mRect.w;}
    [[nodiscard]] int getHeight() const {return mRect.h;}
private:
    SDL_Rect mRect {0, 0, 500, 40};
    std::string mName;
    const MyTexture* mNameTexture = nullptr;
    OptionEntryButton mLeftButton;
    OptionEntryButton mRightButton;
    std::vector<std::string> mOptions;
    std::vector<const MyTexture*> mOptionsTextures;
    int mSelectedOption = 0;
    SettingType mType;
    constexpr static int PADDING = 10;
};


#endif //OPTIONENTRYBOX_HPP
