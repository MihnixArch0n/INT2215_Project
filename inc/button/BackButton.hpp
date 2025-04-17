#ifndef BACKBUTTON_HPP
#define BACKBUTTON_HPP


#include <functional>
#include "button/Button.hpp"


class BackButton : public Button
{
public:
    explicit BackButton(std::function<void()> callback);

    [[nodiscard]] ButtonType getType() const override {return ButtonType::BACK;}

    void onClick(GameState &gameState) override;
private:
    std::function<void()> backToNormalMenu;
};



#endif //BACKBUTTON_HPP
