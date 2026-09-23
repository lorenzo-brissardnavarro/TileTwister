#include "Window.hpp"
#include <iostream>
#include <string>
using namespace std;


// Constructor by initialisation list : Window
Window::Window(std::string title, int width, int height)
    : title(title), width(width), height(height), pWindow(nullptr), pRenderer(nullptr)
{
}


// Method for initialising the window
bool Window::initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        return false;     
    }
    
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    pWindow = SDL_CreateWindow(this->title.c_str(), this->width, this->height, 0);       
    if (pWindow == nullptr) {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return false;     
    }
    
    pRenderer = SDL_CreateRenderer(pWindow, NULL);       
    if (pRenderer == nullptr) {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return false;     
    }
    return true;     
}


// Getter to retrieve the pointer
SDL_Renderer* Window::getRenderer(){
    return this->pRenderer;
}


// Getter to retrieve the pointer
SDL_Window* Window::getWindow(){
    return this->pWindow;
}


// The destructor to free memory
Window::~Window() {
    if (pRenderer != nullptr) {
        SDL_DestroyRenderer(pRenderer);
    }
    if (pWindow != nullptr) {
        SDL_DestroyWindow(pWindow);
    }
    TTF_Quit();
    SDL_Quit();
}


