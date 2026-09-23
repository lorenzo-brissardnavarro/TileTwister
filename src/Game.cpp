#include "Game.hpp"
#include <iostream>
#include <string>
using namespace std;

// Constructor by initialisation list : Game
Game::Game()
    : finalImage(0, 0, 600, 600), targetSelected(false)
{
}


// We call the methods to initialise the grid and load the font
void Game::initialize() {
    grid.initialize();
    grid.loadFont();

}


// Method that manages the display based on the progress of the game
void Game::startInterface(SDL_Renderer* pRenderer) {
    if(!targetSelected) {
        grid.drawChoice(pRenderer);
        return;
    }

    if(grid.findNumber(grid.getTarget())) {
        finalImage.draw(pRenderer, "images/victory.png");
    } else if(!grid.findNumber(0) && !grid.shiftAvailable()) {
        finalImage.draw(pRenderer, "images/defeat.png");
    } else {
        grid.draw(pRenderer);
    }
}


// Method that retrieves the keyboard key and calls the appropriate method
void Game::manageKeyboard(SDL_Event& event) {
    char direction;
    // We retrieve the coordinates of left-click events
    if(!targetSelected) {
        if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            grid.choice(event.button.x, event.button.y);
            if(grid.getTarget() != 0) {
                targetSelected = true;
                grid.newGame();
            }
        }
        return;
    }
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
            this->targetSelected = false;
            return;
        default:
            return;
    }
    // If a move has been made, a new tile is added
    if (grid.move(direction))
        grid.addTile();
        
}
