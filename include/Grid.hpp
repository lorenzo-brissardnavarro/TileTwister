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
    int target;

public:

    Grid();

    void initialize();
    void draw(SDL_Renderer* pRenderer);
    void drawText(SDL_Renderer* pRenderer, std::string text, int x, int y, const SDL_Color& color);
    void drawChoice(SDL_Renderer* pRenderer);
    void addTile();
    void shift(char direction);
    void merge(char direction);
    bool move(char direction);
    bool loadFont();
    bool findNumber(int number);
    bool shiftAvailable();
    void newGame();
    void setTarget(int value);
    int getTarget();
    int getScore();
    void setFontSize(int value);
    void choice(int x, int y);

    ~Grid();

};

#endif