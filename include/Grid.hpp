#ifndef GRID_HPP
#define GRID_HPP
#include <utility>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <random>
#include <vector>
#include <iostream>

class Grid {

private:

    std::vector<std::vector<int>> grid;
    TTF_Font* font;
    std::mt19937 gen;

public:

    Grid();

    void initialize();
    void draw(SDL_Renderer* pRenderer);
    void drawText(SDL_Renderer* pRenderer, std::string text, int x, int y);
    void addTile();
    void leftShift();
    void rightShift();
    void upShift();
    void downShift();
    bool loadFont();

    ~Grid();

};

#endif