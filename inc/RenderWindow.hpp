#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <SDL.h>

class RenderWindow
{
public:
    ~RenderWindow();

    bool create(const char* title, int width, int height);

    [[nodiscard]] SDL_Renderer* getRenderer() const;
private:
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
};


#endif //RENDERWINDOW_HPP
