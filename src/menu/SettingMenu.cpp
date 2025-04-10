#include "menu/SettingMenu.hpp"

#include "button/SettingsButton.hpp"
#include "button/BackButton.hpp"


SettingMenu::SettingMenu(std::function<void()> callback) : setNormalGroup(callback) {}

bool SettingMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    mButtonList.push_back(std::make_unique<BackButton>(setNormalGroup));
    mOptionEntries.push_back(OptionEntryBox(SettingType::MUSIC_ON_OFF));
    mOptionEntries.push_back(OptionEntryBox(SettingType::MUSIC_VOLUME));
    mOptionEntries.push_back(OptionEntryBox(SettingType::SOUND_ON_OFF));
    mOptionEntries.push_back(OptionEntryBox(SettingType::SOUND_VOLUME));
    int i = 1;
    for (auto& option : mOptionEntries)
    {
        option.setPosY(i * (option.getHeight() + PADDING));
        option.init(manager, renderer);
        ++i;
    }
    Menu::init(manager, renderer);
    return true;
}

void SettingMenu::handleEvents(SDL_Event &event, GameState &gameState)
{
    Menu::handleEvents(event, gameState);
    for (auto& option : mOptionEntries) option.handleEvent(event);
}

void SettingMenu::update(GameState &gameState)
{
    Menu::update(gameState);
    for (auto& option : mOptionEntries) option.update();
}

void SettingMenu::render(SDL_Renderer *renderer) const
{
    Menu::render(renderer);
    for (auto option : mOptionEntries) option.render(renderer);
}

