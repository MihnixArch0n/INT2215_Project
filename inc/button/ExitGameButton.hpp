#ifndef EXITBUTTON_HPP
#define EXITBUTTON_HPP


#include "button/Button.hpp"


class ExitGameButton : public Button
{
public:
    ExitGameButton() {mText = "Exit";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::EXIT;}
    void onClick(GameState &gameState) override;
};


#endif //EXITBUTTON_HPP