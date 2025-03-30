#ifndef RESUMEBUTTON_HPP
#define RESUMEBUTTON_HPP


#include "button/Button.hpp"


class ResumeButton : public Button
{
public:
    ResumeButton() {mText = "Resume";}

    void onClick(GameState &gameState) override;
    [[nodiscard]] ButtonType getType() const override {return ButtonType::RESUME;}
};


#endif //RESUMEBUTTON_HPP
