#include "button/OptionEntryBox.hpp"

#include "managers/AudioManager.hpp"
#include "managers/ConfigManager.hpp"

OptionEntryBox::OptionEntryBox(SettingType type) :
    mLeftButton(ButtonType::OPTION_ENTRY_LEFT),
    mRightButton(ButtonType::OPTION_ENTRY_RIGHT),
    mType(type)
{
    if (type == SettingType::MUSIC_ON_OFF) mName = "Music";
    if (type == SettingType::MUSIC_VOLUME) mName = "Music Volume";
    if (type == SettingType::SOUND_ON_OFF) mName = "Sound";
    if (type == SettingType::SOUND_VOLUME) mName = "Sound Volume";

    if (type == SettingType::MUSIC_ON_OFF || type == SettingType::SOUND_ON_OFF)
    {
        mOptions = {"off", "on"};
    }
    else
    {
        for (char c = '0'; c <= '9'; ++c)
        {
            std::string t = "0";
            t += c;
            mOptions.push_back(t);
        }
        mOptions.emplace_back("10");
    }
    mSelectedOption = static_cast<int>(mOptions.size()) - 1;
}

bool OptionEntryBox::init(ResourceManager &resManager, SDL_Renderer *renderer)
{
    resManager.addText(mName, renderer);
    mNameTexture = resManager.getText(mName);
    mLeftButton.init(resManager, renderer);
    mRightButton.init(resManager, renderer);

    int w = mNameTexture->getWidth();
    mLeftButton.setPosX(mRect.x + w + 2 * PADDING);
    mLeftButton.setPosY(mRect.y);
    mRightButton.setPosX(mLeftButton.getPosX() + mLeftButton.getWidth() + PADDING);
    mRightButton.setPosY(mRect.y);
    for (const auto& option : mOptions)
    {
        resManager.addText(option, renderer);
        mOptionsTextures.push_back(resManager.getText(option));
    }
    return true;
}

void OptionEntryBox::handleEvent(SDL_Event &event)
{
    mLeftButton.handleEvent(event);
    mRightButton.handleEvent(event);
}


void OptionEntryBox::update()
{
    GameState trash;
    mLeftButton.update(trash);
    mRightButton.update(trash);

    if (mType == SettingType::MUSIC_ON_OFF)
    {
        mSelectedOption = ConfigManager::getInstance().getMusicStatus();
    }
    else if (mType == SettingType::MUSIC_VOLUME)
    {
        mSelectedOption = ConfigManager::getInstance().getMusicVolume();
    }
    else if (mType == SettingType::SOUND_ON_OFF)
    {
        mSelectedOption = ConfigManager::getInstance().getSoundStatus();
    }
    else if (mType == SettingType::SOUND_VOLUME)
    {
        mSelectedOption = ConfigManager::getInstance().getSoundVolume();
    }

    int size = static_cast<int>(mOptions.size());
    if (mLeftButton.isPressed())
    {
        mSelectedOption = (mSelectedOption - 1 + size) % size;
        mLeftButton.resetButtonState();
    }
    else if (mRightButton.isPressed())
    {
        mSelectedOption = (mSelectedOption + 1) % size;
        mRightButton.resetButtonState();
    }

    if (mType == SettingType::MUSIC_ON_OFF)
    {
        if (mOptions[mSelectedOption] == "on") AudioManager::getInstance().getMusic().play();
        else if (mOptions[mSelectedOption] == "off") AudioManager::stopMusic();
        ConfigManager::getInstance().toogleMusic(mSelectedOption);
    }
    else if (mType == SettingType::SOUND_ON_OFF)
    {
        ConfigManager::getInstance().toogleSound(mSelectedOption);
    }
    else if (mType == SettingType::MUSIC_VOLUME)
    {
        ConfigManager::getInstance().setMusicVolume(mSelectedOption);
        AudioManager::updateMusicVolume();
    }
    else if (mType == SettingType::SOUND_VOLUME)
    {
        ConfigManager::getInstance().setSoundVolume(mSelectedOption);
        AudioManager::getInstance().updateSoundVolume();
    }
}

void OptionEntryBox::render(SDL_Renderer *renderer) const
{
    int x = mRightButton.getPosX();
    int w = mRightButton.getWidth();
    mLeftButton.render(renderer);
    mRightButton.render(renderer);
    mNameTexture->render(mRect.x, mRect.y, renderer);
    mOptionsTextures[mSelectedOption]->render(x + w + 2 * PADDING, mRect.y, renderer);
}

