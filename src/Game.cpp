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
    char direction;
    switch (event.key.key) {
        case SDLK_UP:
            direction = 'u';
            break;
        case SDLK_DOWN:
            direction = 'd';
            break;
        case SDLK_LEFT:
            direction = 'l';
            break;
        case SDLK_RIGHT:
            direction = 'r';
            break;
        default:
            return;
    }
    if (grid.move(direction))
        grid.addTile();
        
}
