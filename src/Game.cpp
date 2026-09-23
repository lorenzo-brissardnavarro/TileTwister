#include "Game.hpp"
#include <iostream>
#include <string>
using namespace std;

Game::Game()
    : finalImage(0, 0, 600, 600)
{
}


void Game::initialize() {
    grid.initialize();
    grid.loadFont();

}

void Game::startInterface(SDL_Renderer* pRenderer) {
    if(grid.findNumber(2048)) {
        finalImage.draw(pRenderer, "images/victory.png");
    } else if(!grid.findNumber(0) && !grid.shiftAvailable()) {
        finalImage.draw(pRenderer, "images/defeat.png");
    } else {
        grid.draw(pRenderer);
    }
    
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
        case SDLK_R:
            grid.newGame();
            break;
        default:
            return;
    }
    if (grid.move(direction))
        grid.addTile();
        
}
