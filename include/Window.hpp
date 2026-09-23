#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Class representing the game window 
class Window {

private:

    std::string title;
    int width;
    int height;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

public:

    Window(std::string title, int width, int height);

    bool initialize();
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    ~Window();
};

#endif