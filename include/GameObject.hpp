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

public:

    // Constructeur de la classe abstraite
    GameObject(int coordinateX, int coordinateY, int sizeX, int sizeY);

    virtual void draw(SDL_Renderer* pRenderer) = 0;
};


// Classe enfant tuile qui hérite de la classe GameObject
class Tile : public GameObject {

private:
    const SDL_Color& color;

public:

    Tile(int coordinateX, int coordinateY, int sizeX, int sizeY, const SDL_Color& color);

    void draw(SDL_Renderer* pRenderer) override;
};


// Classe enfant image qui hérite de la classe GameObject
class Image : public GameObject {

public:

    using GameObject::draw;

    Image(int coordinateX, int coordinateY, int sizeX, int sizeY);

    void draw(SDL_Renderer* pRenderer) override;
    void draw(SDL_Renderer* pRenderer, std::string path);
};

#endif