#include "Game.hpp"
#include "Window.hpp"
#include "GameObject.hpp"
using namespace std;

int main() {

    Window window("Tile Twister", 600, 700);
    window.initialize();

    Game game;
    game.initialize();

    SDL_Event events;
    bool open = true;

    Image duck(600, 605, 120, 100);
    float speed = 125.0f;
    Uint64 last_time = SDL_GetTicks();

    
    while (open) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                // if you click on the cross, the window closes
                case SDL_EVENT_QUIT:
                    open = false;
                    break;
                // we listen for other events, including those from the keyboard
                case SDL_EVENT_KEY_DOWN:
                    game.manageKeyboard(events);
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    game.manageKeyboard(events);
                    break;
            }
        }
        Uint64 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        int value = duck.getCoordinateX() - speed * delta_time;
        duck.setCoordinateX(value);

        if (duck.getCoordinateX() + duck.getSizeX() < 0) {
            duck.setCoordinateX(600);
        }

        SDL_SetRenderDrawColor(window.getRenderer(), 14, 36, 51, 255);
        SDL_RenderClear(window.getRenderer());

        game.startInterface(window.getRenderer());
        duck.draw(window.getRenderer(), "images/duck.png");
        
        SDL_RenderPresent(window.getRenderer());

        SDL_Delay(16);
    }
}