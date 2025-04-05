#ifndef SETTINGSBUTTON_HPP
#define SETTINGSBUTTON_HPP


#include <functional>
#include "button/Button.hpp"


class SettingsButton : public Button
{
public:
    explicit SettingsButton(std::function<void()> callback);


    [[nodiscard]] ButtonType getType() const override {return ButtonType::SETTINGS;}
    void onClick(GameState &gameState) override;

private:
    std::function<void()> goToSettingMenu;
};



#endif //SETTINGSBUTTON_HPP
