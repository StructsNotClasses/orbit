#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include "game.h"
constexpr int SCREEN_WIDTH{640};
constexpr int SCREEN_HEIGHT{800};

void updateObjects() {
}

int main(int argc, char* args[]) {
	//create main window
	Game* main = new Game();

	assert(main->init() && "Initialization Failed");

	main->update();

	SDL_Delay( 2000 ); 

	SDL_Event lol;
	bool running{1};
	while(running) {
		while(SDL_PollEvent(&lol)) {
			running = main->event(&lol);
			//improve the key system so that keydown and keyup events are accounted for; smooth movement
		}
		main->update();
		SDL_Delay(50);
	}

	
	main->quit();
	std::cout << "Program exited successfully\n";
	delete main;
	

	return 0;  
}
