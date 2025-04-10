#ifndef MENU_HPP
#define MENU_HPP


#include <SDL.h>
#include <vector>
#include <memory>

#include "defs.hpp"
#include "managers/ResourceManager.hpp"
#include "button/Button.hpp"


class Menu
{
public:
    virtual ~Menu() = default;

    virtual bool init(ResourceManager& manager, SDL_Renderer* renderer);
    virtual void handleEvents(SDL_Event& event, GameState& gameState);
    virtual void update(GameState& gameState);
    virtual void render(SDL_Renderer* renderer) const;


    static constexpr SDL_Color BG_COLOR {0xE9, 0xF2, 0xCF, 0xFF};
protected:
    SDL_Rect mRect {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    bool hidden = false;
    std::vector<std::unique_ptr<Button>> mButtonList;
    constexpr static int PADDING = 10;
};


#endif //MENU_HPP
