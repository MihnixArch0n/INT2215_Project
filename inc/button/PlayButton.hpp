#ifndef PLAYBUTTON_HPP
#define PLAYBUTTON_HPP


#include "button/Button.hpp"


class PlayButton : public Button
{
public:
    PlayButton() {mText = "Play";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::PLAY;}
    void onClick(GameState &gameState) override;
};



#endif //PLAYBUTTON_HPP
