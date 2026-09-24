#include "Grid.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

// Constructor by initialisation list : Grid
Grid::Grid()
    : grid(4, std::vector<int>(4, 0)), font(nullptr), gen(std::random_device{}()), score(0), target(0)
{
}


// Method for loading the font contained in the “fonts” folder
bool Grid::loadFont() {
    font = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 20);
    return font != nullptr;
}


// Method for initialising the grid by filling it with zeros and placing the two starting tiles
void Grid::initialize() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            grid[i][j] = 0;
        }
    }
    addTile();
    addTile();
}


// Method for adding a random tile to the grid
void Grid::addTile() {
    std::uniform_int_distribution<int> distribPosition(0, 3); // A random number between 0 and 3 for the position
    std::uniform_int_distribution<int> distribValue(1, 10); // A random number to determine the tile’s value (2 or 4) based on probabilities

    int row;
    int column;

    do {
        row = distribPosition(gen);
        column = distribPosition(gen);
    } while (grid[row][column] != 0);

    // 90% chance of a 2 appearing and 10% chance of a 4 appearing
    if (distribValue(gen) <= 9) {
        grid[row][column] = 2;
    } else {
        grid[row][column] = 4;
    }
}


// Method for displaying text
void Grid::drawText(SDL_Renderer* pRenderer, std::string text, int x, int y, const SDL_Color& color) {
    SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
    if (surface == nullptr) {
        return;
    }
        
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if (texture == nullptr) {
        SDL_DestroySurface(surface);
        return;
    }

    // The number is centred relative to the tile’s size
    float texteX = x + (90 - surface->w) / 2.0f;
    float texteY = y + (90 - surface->h) / 2.0f;

    SDL_FRect destination = {texteX, texteY, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(pRenderer, texture, nullptr, &destination);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}


// Method for displaying the grid
void Grid::draw(SDL_Renderer* pRenderer) {

    //The live score is displayed
    drawText(pRenderer, "Score : " + std::to_string(this->score), 90, 30, { 255, 255, 0, 255 });
    drawText(pRenderer, "Objectif : ", 340, 30, { 255, 255, 0, 255 });
    SDL_Color color = { 0, 0, 0, 255 };
    if(target == 1024) {
        color = { 220, 80, 120, 255 };
    } else if (target == 2048) {
        color = { 180, 60, 160, 255 };
    } else {
        color = { 100, 40, 220, 255 };
    }
    Tile tileTarget(460, 25, 90, 90, color);
    tileTarget.draw(pRenderer);
    drawText(pRenderer, std::to_string(this->target), 460, 25, { 0, 0, 0, 255 });
    
    // We create the background of the game board
    Tile boardGame(75, 125, 450, 450, { 28, 73, 102, 255 });
    boardGame.draw(pRenderer);

    // We go through our 16 cell
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = 105 + j * 100;
            int y = 155 + i * 100;

            SDL_Color color = { 41, 109, 152, 255 };

            // The colour of the tile is determined by the value in the cell
            switch(grid[i][j]) {
                case 2:
                    color = { 238, 228, 218, 255 };
                    break;
                case 4:
                    color = { 232, 220, 200, 255 };
                    break;
                case 8:
                    color = { 255, 183, 120, 255 };
                    break;
                case 16:
                    color = { 255, 150, 90, 255 };
                    break;
                case 32:
                    color = { 255, 120, 80, 255 };
                    break;
                case 64:
                    color = { 255, 90, 60, 255 };
                    break;
                case 128:
                    color = { 240, 180, 70, 255 };
                    break;
                case 256:
                    color = { 255, 160, 50, 255 };
                    break;
                case 512:
                    color = { 255, 130, 40, 255 };
                    break;
                case 1024:
                    color = { 220, 80, 120, 255 };
                    break;
                case 2048:
                    color = { 180, 60, 160, 255 };
                    break;
                case 4096:
                    color = { 140, 50, 200, 255 };
                    break;
                case 8192:
                    color = { 100, 40, 220, 255 };
                    break;
                default:
                    break;
            }

            // For each cell in the grid, a tile is created and displayed
            Tile tileGame(x, y, 90, 90, color);
            tileGame.draw(pRenderer);

            // If the cell contains a value, it is displayed on top of the tile
            if (grid[i][j] != 0) {
                drawText(pRenderer, std::to_string(grid[i][j]), x, y, { 0, 0, 0, 255 });
            }
        }
    }
}


// Method for the opening screen to select the tile to reach in order to win the game
void Grid::drawChoice(SDL_Renderer* pRenderer) {
    drawText(pRenderer, "Votre objectif", 260, 30, { 255, 255, 0, 255 });
    int choices[] = { 1024, 2048, 8192 };
    SDL_Color colors[] = {{ 69, 182, 254, 255 }, { 41, 109, 152, 255 }, { 28, 73, 102, 255 }};
    for(int i = 0 ; i < 3 ; i++) {
        Tile choice(240, (i + 1) * 150, 120, 120, colors[i]);
        choice.draw(pRenderer);
        drawText(pRenderer, std::to_string(choices[i]), 255, (i + 1) * 150 + 15, { 255, 255, 255, 255 });
    }
}


// Method for managing movements by sorting the grid
void Grid::shift(char direction) {
    switch(direction) {
        // All the numbers in the row are shifted to the left
        case 'l':
            for(int i = 0 ; i < 4 ; i++) {
                stable_partition(grid[i].begin(), grid[i].end(), [](int n) {
                    return n != 0;
                });
            }
            break;

        // All the numbers in the row are shifted to the right
        case 'r':
            for(int i = 0 ; i < 4 ; i++) {
                stable_partition(grid[i].begin(), grid[i].end(), [](int n) {
                    return n == 0;
                });
            }
            break;

        // The numbers in the column are grouped together before being sorted from left to right
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

        // The numbers in the column are grouped together before being sorted from right to left
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


// Method for calculating the merging of two tiles along a given direction
void Grid::merge(char direction) {
    switch(direction) {
        // We scan the line from left to right
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

        // We scan the line from right to left
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

        // We scan the column from left to right
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

        // We scan the column from right to left
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


// Method for managing correct movement and merging according to direction
bool Grid::move(char direction) {
    auto oldGrid = grid;
    shift(direction);
    merge(direction); 
    shift(direction); // Move again after a merge
    return oldGrid != grid; // We check if the grid has changed and therefore if we need to add a new tile or not
}


// Method for searching for a specific value in the grid (used for 0 and 2048 in particular)
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


// Method for checking if you can still make a move and therefore the game is not over
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


// Method for starting a new game
void Grid::newGame() {
    initialize();
    this->score = 0;
    setFontSize(20);
}


// Setter to change the target value
void Grid::setTarget(int value) {
    this->target = value;
}


// Setter to change the font's size
void Grid::setFontSize(int value) {
    float newSize = value; 
    if (!TTF_SetFontSize(this->font, newSize)) {
        std::cerr << "Erreur lors du changement de taille: " << SDL_GetError() << std::endl;
    }
}


// Getter to retrieve the target value
int Grid::getTarget() {
    return this->target;
}


// Getter to retrieve the score value
int Grid::getScore() {
    return this->score;
}


// A method for determining, based on the position on the screen, what the objective is for that game
void Grid::choice(int x, int y) {
    if(x >= 240 && x <= 360 && y >= 150 && y <= 270) {
        this->target = 1024;
    } else if(x >= 240 && x <= 360 && y >= 300 && y <= 420) {
        this->target = 2048;
    } else if(x >= 240 && x <= 360 && y >= 450 && y <= 570) {
        this->target = 8192;
    }
}


// The destructor to free memory
Grid::~Grid() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}