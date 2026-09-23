#ifndef GRID_HPP
#define GRID_HPP
#include <utility>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <random>
#include <vector>
#include <iostream>

// Class representing the game grid as a two-dimensional vector
class Grid {

private:

    std::vector<std::vector<int>> grid;
    TTF_Font* font;
    std::mt19937 gen;
    int score;

public:

    Grid();

    void initialize();
    void draw(SDL_Renderer* pRenderer);
    void drawText(SDL_Renderer* pRenderer, std::string text, int x, int y);
    void addTile();
    void shift(char direction);
    void merge(char direction);
    bool move(char direction);
    bool loadFont();
    bool findNumber(int number);
    bool shiftAvailable();
    void newGame();

    ~Grid();

};

#endif