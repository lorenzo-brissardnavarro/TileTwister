#include "Grid.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;


Grid::Grid()
    : grid(4, std::vector<int>(4, 0)), font(nullptr), gen(std::random_device{}()), score(0)
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
    drawText(pRenderer, "Score : " + std::to_string(this->score), 105, 30);
    Tile boardGame(75, 125, 450, 450, { 136, 129, 129, 255 });
    boardGame.draw(pRenderer);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = 105 + j * 100;
            int y = 155 + i * 100;

            SDL_Color color = { 196, 181, 181, 255 };

            switch(grid[i][j]) {
                case 2:
                    color = { 238, 228, 218, 255 };
                    break;
                case 4:
                    color = { 237, 224, 200, 255 };
                    break;
                case 8:
                    color = { 242, 177, 121, 255 };
                    break;
                case 16:
                    color = { 245, 149, 99, 255 };
                    break;
                case 32:
                    color = { 246, 124, 95, 255 };
                    break;
                case 64:
                    color = { 246, 94, 59, 255 };
                    break;
                case 128:
                    color = { 237, 207, 114, 255 };
                    break;
                case 256:
                    color = { 237, 204, 97, 255 };
                    break;
                case 512:
                    color = { 237, 200, 80, 255 };
                    break;
                case 1024:
                    color = { 237, 197, 63, 255 };
                    break;
                case 2048:
                    color = { 237, 194, 46, 255 };
                    break;
                default:
                    break;
            }

            Tile tileGame(x, y, 90, 90, color);
            tileGame.draw(pRenderer);

            if (grid[i][j] != 0) {
                drawText(pRenderer, std::to_string(grid[i][j]), x, y);
            }
        }
    }
}




void Grid::shift(char direction) {
    switch(direction) {
        case 'l':
            for(int i = 0 ; i < 4 ; i++) {
                stable_partition(grid[i].begin(), grid[i].end(), [](int n) {
                    return n != 0;
                });
            }
            break;

        case 'r':
            for(int i = 0 ; i < 4 ; i++) {
                stable_partition(grid[i].begin(), grid[i].end(), [](int n) {
                    return n == 0;
                });
            }
            break;

        case 'u':
            for(int i = 0 ; i < 4 ; i++) {
                std::vector<int> temp(4);
                for(int j = 0 ; j < 4 ; j++) {
                    temp[j] = grid[j][i];
                }
                stable_partition(temp.begin(), temp.end(), [](int n) {
                    return n != 0;
                });
                for(int j = 0 ; j < 4 ; j++) {
                    grid[j][i] = temp[j];
                }
            }
            break;

        case 'd':
            for(int i = 0 ; i < 4 ; i++) {
                std::vector<int> temp(4);
                for(int j = 0 ; j < 4 ; j++) {
                    temp[j] = grid[j][i];
                }
                stable_partition(temp.begin(), temp.end(), [](int n) {
                    return n == 0;
                });
                for(int j = 0 ; j < 4 ; j++) {
                    grid[j][i] = temp[j];
                }
            }
            break;
    }
}





void Grid::merge(char direction) {
    switch(direction) {
        case 'l':
            for(int i = 0 ; i < 4 ; i++) {
                for(int j = 0 ; j < 3 ; j++) {
                    if(grid[i][j] == grid[i][j+1]){
                        this->score += grid[i][j];
                        grid[i][j] *= 2;
                        grid[i][j+1] = 0;
                    }
                }
            }
            break;

        case 'r':
            for(int i = 0 ; i < 4 ; i++) {
                for(int j = 3 ; j > 0 ; j--) {
                    if(grid[i][j] == grid[i][j-1]){
                        this->score += grid[i][j];
                        grid[i][j] *= 2;
                        grid[i][j-1] = 0;
                    }
                }
            }
            break;

        case 'u':
            for(int i = 0 ; i < 4 ; i++) {
                for(int j = 0 ; j < 3 ; j++) {
                    if(grid[j][i] == grid[j+1][i]){
                        this->score += grid[j][i];
                        grid[j][i] *= 2;
                        grid[j+1][i] = 0;
                    }
                }
            }
            break;

        case 'd':
            for(int i = 0 ; i < 4 ; i++) {
                for(int j = 3 ; j > 0 ; j--) {
                    if(grid[j][i] == grid[j-1][i]){
                        this->score += grid[j][i];
                        grid[j][i] *= 2;
                        grid[j-1][i] = 0;
                    }
                }
            }
            break;
    }
}



bool Grid::move(char direction) {
    auto oldGrid = grid;
    shift(direction);
    merge(direction);
    shift(direction);
    return oldGrid != grid;
}

bool Grid::findNumber(int number) {
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            if(grid[i][j] == number){
                return true;
            }
        }
    }
    return false;
}

bool Grid::shiftAvailable() {
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 3 ; j++) {
            if((grid[i][j] == grid[i][j+1]) || (grid[j][i] == grid[j+1][i])){
                return true;
            }
        }
    }
    return false;
}




// Destructeur pour libérer la mémoire
Grid::~Grid() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}