#ifndef OPTIONENTRYBUTTON_HPP
#define OPTIONENTRYBUTTON_HPP


#include "button/Button.hpp"


class OptionEntryButton : public Button
{
public:
    explicit OptionEntryButton(ButtonType type);
    bool init(ResourceManager &resManager, SDL_Renderer *renderer) override;

    [[nodiscard]] ButtonType getType() const override;

    void onClick(GameState &gameState) override;
private:
    ButtonType mType;
};



#endif //OPTIONENTRYBUTTON_HPP
