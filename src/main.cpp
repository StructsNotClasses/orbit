#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include <limits>
#include "game.h"
#include "helpers.h"

void updateObjects() {
}

int main(int argc, char* args[]) {
	double* yeet = gravitationalAcceleration(10,0,-10,0,1000,1000,1);
	if(yeet[0] == std::numeric_limits<double>::infinity()) yeet[0] = 0;
	if(yeet[1] == std::numeric_limits<double>::infinity()) yeet[1] = 0;
	
	std::cout << "x: " << yeet[0] << "y: " << yeet[1] << '\n';
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
