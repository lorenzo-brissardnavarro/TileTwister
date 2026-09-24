#ifndef GAME_HPP
#define GAME_HPP

#include "Grid.hpp"
#include "GameObject.hpp"
#include "Window.hpp"

// Contains the grid and is responsible for displaying it and detecting keys pressed on the keyboard
class Game {

private:
    Grid grid;
    Image finalImage;
    bool targetSelected;
    bool gameInProgress;

public:
    Game();

    void initialize();
    void startInterface(SDL_Renderer* pRenderer);
    void manageKeyboard(SDL_Event& event);
    
};

#endif