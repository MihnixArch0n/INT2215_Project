#ifndef QUITBUTTON_HPP
#define QUITBUTTON_HPP


#include "button/Button.hpp"


class QuitButton : public Button
{
public:
    QuitButton() {mText = "Quit to Title";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::QUIT;}
    void onClick(GameState &gameState) override;
};


#endif //QUITBUTTON_HPP
