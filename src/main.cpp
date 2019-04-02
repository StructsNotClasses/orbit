#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include "game.h"
#include "helpers.h"
constexpr int SCREEN_WIDTH{640};
constexpr int SCREEN_HEIGHT{480};

void updateObjects() {
}

int main(int argc, char* args[]) {
	//create main window
	Game* main = new Game();

	assert(main->init() && "Initialization Failed");

	main->update();

	SDL_Delay( 2000 ); 

	assert(main->player && "player uninitialized");

	//read input and change values based on it
	SDL_Event event;
	bool running{1};
	while(running) {
		while(SDL_PollEvent(&event)) {
			running = main->event(&event);
		}
		main->update();
		SDL_Delay(50);
	}

	
	main->quit();
	std::cout << "Program exited successfully\n";
	delete main;
	

	return 0;  
}
