#include "GameObject.hpp"
#include <iostream>
using namespace std;

// Constructeur liste d'initiation
GameObject::GameObject(int coordinateX, int coordinateY, int sizeX, int sizeY, const SDL_Color& color)
    : coordinateX(coordinateX), coordinateY(coordinateY), sizeX(sizeX), sizeY(sizeY), color(color)
{
}

Tile::Tile(int coordinateX, int coordinateY, int sizeX, int sizeY, const SDL_Color& color)
    : GameObject(coordinateX, coordinateY, sizeX, sizeY, color)
{
}

void Tile::draw(SDL_Renderer* pRenderer) {
    SDL_FRect tileGame = {(float)this->coordinateX, (float)this->coordinateY, (float)this->sizeX, (float)this->sizeY};
    SDL_SetRenderDrawColor(pRenderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderFillRect(pRenderer, &tileGame);
}

