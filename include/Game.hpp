#ifndef GAME_HPP
#define GAME_HPP

#include "Grid.hpp"
#include "GameObject.hpp"

class Game {

private:
    Grid grid;

public:
    Game();

    void initialize(SDL_Renderer* pRenderer);
    void startInterface(SDL_Renderer* pRenderer);
    void manageKeyboard(SDL_Event& event);
};

#endif