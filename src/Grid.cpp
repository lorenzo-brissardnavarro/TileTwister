#include "Grid.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <vector>
#include <utility>
using namespace std;


Grid::Grid()
    : grid{}, font(nullptr)
{
}



bool Grid::loadFont() {
    font = TTF_OpenFont("fonts/BebasNeue-Regular.ttf", 38);
    return font != nullptr;
}


void Grid::draw(SDL_Renderer* pRenderer) {
    Tile boardGame(75, 75, 450, 450, { 136, 129, 129, 255 });
    boardGame.draw(pRenderer);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = 105 + j * 100;
            int y = 105 + i * 100;

            Tile tileGame(x, y, 90, 90, { 196, 181, 181, 255 });
            tileGame.draw(pRenderer);
        }
    }
}


