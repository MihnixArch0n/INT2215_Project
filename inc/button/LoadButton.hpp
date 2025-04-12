#ifndef LOADBUTTON_HPP
#define LOADBUTTON_HPP


#include "button/Button.hpp"


class LoadButton : public Button
{
public:
    LoadButton() {mText = "Load";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::LOAD;}

    void onClick(GameState &gameState) override;
};



#endif //LOADBUTTON_HPP
