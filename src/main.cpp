#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include <limits>
#include "game.h"
#include "timer.h"
#include "helpers.h"

constexpr int FRAMERATE{60};

int main(int argc, char *args[])
{
    srand(time(NULL));

    //create main window
    Game *main = new Game();

    assert(main->init(0, 0, 4) && "Initialization Failed");
    bool tmp{1};
    main->update(tmp);
    main->newSystem();

    //read input and change values based on it
    SDL_Event event;
    bool running{1};
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            running = main->event(&event);
        }
        main->update(running);
        SDL_Delay(1000 / FRAMERATE);
    }

    main->quit();
    std::cout << "Program exited successfully\n";
    delete main;

    return 0;
}
