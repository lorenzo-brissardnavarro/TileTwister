#include "Game.hpp"
#include <iostream>
#include <string>
using namespace std;

Game::Game()
{
}


void Game::initialize(SDL_Renderer* pRenderer) {
    grid.initialize();
    grid.loadFont();

}

void Game::startInterface(SDL_Renderer* pRenderer) {
    grid.draw(pRenderer);
}


void Game::manageKeyboard(SDL_Event& event) {
    switch (event.key.key) {
        case SDLK_UP:
            grid.upShift();
            break;
        case SDLK_DOWN:
            grid.downShift();
            break;
        case SDLK_LEFT:
            grid.leftShift();
            break;
        case SDLK_RIGHT:
            grid.rightShift();
            break;
        default:
            break;
    }
}
