#ifndef PLAYAGAINBUTTON_HPP
#define PLAYAGAINBUTTON_HPP


#include "button/Button.hpp"


class PlayAgainButton : public Button
{
public:
    PlayAgainButton() {mText = "Play Again";}

    [[nodiscard]] ButtonType getType() const override {return ButtonType::PLAY_AGAIN;}

    void onClick(GameState &gameState) override;
};



#endif //PLAYAGAINBUTTON_HPP
