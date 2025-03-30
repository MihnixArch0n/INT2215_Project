#ifndef BUTTON_HPP
#define BUTTON_HPP


#include <SDL.h>
#include <string>

#include "defs.hpp"
#include "MyTexture.hpp"
#include "ResourceManager.hpp"


class Button
{
public:
    Button() : mRect({0, 0, 32, 32}) {}
    virtual ~Button() = default;

    virtual bool init(ResourceManager& resManager, SDL_Renderer* renderer);
    void handleEvent(SDL_Event &event);
    virtual void update(GameState& gameState);
    void render(SDL_Renderer* renderer) const;

    [[nodiscard]] virtual ButtonType getType() const = 0;

    [[nodiscard]] const SDL_Rect& getRect() const {return mRect;}

    void setPosX(int x) {mRect.x = x;}
    void setPosY(int y) {mRect.y = y;}
    [[nodiscard]] int getWidth() const {return mRect.w;}
    [[nodiscard]] int getHeight() const {return mRect.h;}

    [[nodiscard]] bool isPressed() const {return pressed;}
    [[nodiscard]] bool isHovered() const {return hovered;}


    virtual void onClick(GameState& gameState) = 0;
    void resetButtonState();

    static constexpr SDL_Color NORMAL_COLOR {0x85, 0xFF, 0xBC, 0xFF};
    static constexpr SDL_Color HOVERED_COLOR {0x1F, 0xFF, 0x84, 0xFF};
    static constexpr SDL_Color PRESSED_COLOR {0x00, 0xA3, 0x49, 0xFF};
protected:
    std::string mText;
    bool pressed = false;
    bool hovered = false;
    SDL_Rect mRect;
    const MyTexture* mTexture = nullptr;
    const SDL_Color* mBgColor = &NORMAL_COLOR;
};


#endif //BUTTON_HPP