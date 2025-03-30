#include "button/ExitGameButton.hpp"

void ExitGameButton::onClick(GameState &gameState)
{
    SDL_Event event {SDL_QUIT};
    SDL_PushEvent(&event);
}
