#ifndef GRID_HPP
#define GRID_HPP
#include <utility>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Grid {

private:

    int grid[4][4];
    TTF_Font* font;

public:

    Grid();

    void draw(SDL_Renderer* pRenderer);
    bool loadFont();

};

#endif