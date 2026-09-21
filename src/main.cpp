#include "Game.hpp"
#include "Window.hpp"
#include "GameObject.hpp"
using namespace std;

int main() {

    Window window("Tile Twister", 600, 600);
    window.initialize();

    Game game;
    game.initialize(window.getRenderer());

    SDL_Event events;
    bool open = true;
    

    while (open) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_EVENT_QUIT:
                    open = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    // game.manageKeyboard(events);
                    break;
            }
        }
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(window.getRenderer());

        game.startInterface(window.getRenderer());

        SDL_RenderPresent(window.getRenderer());

        SDL_Delay(16);
    }
}