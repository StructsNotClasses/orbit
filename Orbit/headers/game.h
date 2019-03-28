#pragma once
#include <SDL2/SDL.h>

class Game {
	public:
		//Game();
		//~Game();
	public:
		bool init();
		bool event(SDL_Event* event);
		void update();
		void quit();
	
	private:
		SDL_Surface* screen{NULL};
		SDL_Window* game_window{NULL};
};
	
