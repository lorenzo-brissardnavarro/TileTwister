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


// void Jeu::manageKeyboard(SDL_Event& event) {
//     switch (event.key.key) {
//         case SDLK_UP:
//             grid.deplacerSelection(0, -1);
//             break;
//         case SDLK_DOWN:
//             grid.deplacerSelection(0, 1);
//             break;
//         case SDLK_LEFT:
//             grid.deplacerSelection(-1, 0);
//             break;
//         case SDLK_RIGHT:
//             grid.deplacerSelection(1, 0);
//             break;
//         default:
//             break;
//     }
// }
