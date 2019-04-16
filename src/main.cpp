#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include <limits>
#include "game.h"
#include "helpers.h"

constexpr int FRAMERATE{60};

int main(int argc, char* args[]) {
	//create main window
	Game* main = new Game();

	assert(main->init(0,0,4) && "Initialization Failed");

	main->update();

	assert(main->player && "player uninitialized");

	//read input and change values based on it
	SDL_Event event;
	bool running{1};
	while(running) {
		while(SDL_PollEvent(&event)) {
			running = main->event(&event);
		}
		main->update();
		SDL_Delay(1000/FRAMERATE);
	}


	main->quit();
	std::cout << "Program exited successfully\n";
	delete main;


	return 0;
}
