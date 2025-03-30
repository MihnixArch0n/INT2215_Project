#ifndef SETTINGSBUTTON_HPP
#define SETTINGSBUTTON_HPP


#include "button/Button.hpp"


class SettingsButton : public Button
{
public:
    SettingsButton() {mText = "Settings";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::SETTINGS;}
    void onClick(GameState &gameState) override;
};



#endif //SETTINGSBUTTON_HPP
