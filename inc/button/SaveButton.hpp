#ifndef SAVEBUTTON_HPP
#define SAVEBUTTON_HPP


#include "button/Button.hpp"


class SaveButton : public Button
{
public:
    SaveButton() {mText = "Save";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::SAVE;}

    void onClick(GameState &gameState) override;
};



#endif //SAVEBUTTON_HPP
