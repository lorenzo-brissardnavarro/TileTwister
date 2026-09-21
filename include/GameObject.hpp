#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>

// Classe abstraite
class GameObject {

protected:
    int coordinateX;
    int coordinateY;
    int sizeX;
    int sizeY;
    const SDL_Color& color;

public:

    // Constructeur de la classe abstraite
    GameObject(int coordinateX, int coordinateY, int sizeX, int sizeY, const SDL_Color& color);

    virtual void draw(SDL_Renderer* pRenderer) = 0;
};


// Classe enfant tuile qui hérite de la classe GameObject
class Tile : public GameObject {

public:

    Tile(int coordinateX, int coordinateY, int sizeX, int sizeY, const SDL_Color& color);

    void draw(SDL_Renderer* pRenderer) override;
};

#endif