#ifndef GAME_HPP
#define GAME_HPP

#include "Grid.hpp"
#include "GameObject.hpp"

class Game {

private:
    Grid grid;
    Image finalImage;

public:
    Game();

    void initialize();
    void startInterface(SDL_Renderer* pRenderer);
    void manageKeyboard(SDL_Event& event);
};

#endif