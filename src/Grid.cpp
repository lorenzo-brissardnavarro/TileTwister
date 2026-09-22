#include "Grid.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;


Grid::Grid()
    : grid(4, std::vector<int>(4, 0)), font(nullptr), gen(std::random_device{}())
{
}



bool Grid::loadFont() {
    font = TTF_OpenFont("fonts/BebasNeue-Regular.ttf", 48);
    return font != nullptr;
}

void Grid::initialize() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            grid[i][j] = 0;
        }
    }

    addTile();
    addTile();
}


void Grid::addTile() {
    std::uniform_int_distribution<int> distribPosition(0, 3);
    std::uniform_int_distribution<int> distribValue(1, 10);

    int row;
    int column;

    do {
        row = distribPosition(gen);
        column = distribPosition(gen);
    } while (grid[row][column] != 0);

    if (distribValue(gen) <= 9) {
        grid[row][column] = 2;
    } else {
        grid[row][column] = 4;
    }
}


void Grid::drawText(SDL_Renderer* pRenderer, std::string text, int x, int y) {
    SDL_Color color = { 0, 0, 0, 255 };

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
    if (surface == nullptr) {
        return;
    }
        
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if (texture == nullptr) {
        SDL_DestroySurface(surface);
        return;
    }
    float texteX = x + (90 - surface->w) / 2.0f;
    float texteY = y + (90 - surface->h) / 2.0f;

    SDL_FRect destination = {texteX, texteY, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(pRenderer, texture, nullptr, &destination);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
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

            if (grid[i][j] != 0) {
                drawText(pRenderer, std::to_string(grid[i][j]), x, y);
            }
        }
    }
}


void Grid::leftShift() {
    for(int i = 0 ; i < 3 ; i++) {
        stable_partition(grid[i].begin(), grid[i].end(), [](int n) { 
            return n != 0; 
        });
    }
}


// Destructeur pour libérer la mémoire
Grid::~Grid() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}