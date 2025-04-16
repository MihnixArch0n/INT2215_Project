#include "menu/SettingMenu.hpp"

#include <utility>

#include "button/SettingsButton.hpp"
#include "button/BackButton.hpp"


SettingMenu::SettingMenu(std::function<void()> callback) : setNormalGroup(std::move(callback)) {}

bool SettingMenu::init(ResourceManager &manager, SDL_Renderer *renderer)
{
    mButtonList.push_back(std::make_unique<BackButton>(setNormalGroup));
    mOptionEntries.emplace_back(SettingType::MUSIC_ON_OFF);
    mOptionEntries.emplace_back(SettingType::MUSIC_VOLUME);
    mOptionEntries.emplace_back(SettingType::SOUND_ON_OFF);
    mOptionEntries.emplace_back(SettingType::SOUND_VOLUME);
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
    for (const auto& option : mOptionEntries) option.render(renderer);
}

