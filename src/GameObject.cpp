#include "GameObject.hpp"
#include <iostream>
using namespace std;


// Constructor by initialisation list : GameObject
GameObject::GameObject(int coordinateX, int coordinateY, int sizeX, int sizeY)
    : coordinateX(coordinateX), coordinateY(coordinateY), sizeX(sizeX), sizeY(sizeY)
{
}


// Constructor by initialisation list : Tile
Tile::Tile(int coordinateX, int coordinateY, int sizeX, int sizeY, const SDL_Color& color)
    : GameObject(coordinateX, coordinateY, sizeX, sizeY),
    color(color)
{
}


// Method for drawing a tile
void Tile::draw(SDL_Renderer* pRenderer) {
    SDL_FRect tileGame = {(float)this->coordinateX, (float)this->coordinateY, (float)this->sizeX, (float)this->sizeY};
    SDL_SetRenderDrawColor(pRenderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderFillRect(pRenderer, &tileGame);
}


// Constructor by initialisation list : Image
Image::Image(int coordinateX, int coordinateY, int sizeX, int sizeY)
    : GameObject(coordinateX, coordinateY, sizeX, sizeY)
{
}



void Image::draw(SDL_Renderer* pRenderer){
    return;
}


// Overload method for displaying an image, as we need the path
void Image::draw(SDL_Renderer* pRenderer, std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        return;
    }
        
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if (texture == nullptr) {
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect destination = {(float)this->coordinateX, (float)this->coordinateY, (float)this->sizeX, (float)this->sizeY};
    SDL_RenderTexture(pRenderer, texture, nullptr, &destination);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

