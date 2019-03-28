#include <iostream>
#include "game.h" 
#include "helpers.h"
bool Game::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	
	game_window = SDL_CreateWindow("wheeeeeee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );

	if(game_window == NULL) return false;

	screen = SDL_GetWindowSurface(game_window);

	if(screen == NULL) return false;
	
	test = surfaceFromBMP("assets/rocket.bmp");
	if(test == NULL) return false;

	if(!drawToSurface(screen, test, 100, 100, 0, 0, 1000, 1000)) return false;

	return true;
}

void Game::update() {
	x+=vx;
	y+=vy;
	drawToSurface(screen, test, x, y, 0, 0, 50, 50); 
	SDL_UpdateWindowSurface(game_window);
}

bool Game::event(SDL_Event* event) {
	switch(event->type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			std::cout << "key was pressed lol\n";
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << '\n';
			if(event->key.keysym.sym == SDLK_w) vy+=1;
			return true;
		case SDL_KEYUP:
			std::cout << "key was released lol\n";
			return true;
		default:
			return true;

	}
}
	

void Game::quit() {
	SDL_FreeSurface(screen);
	SDL_FreeSurface(test);
	SDL_DestroyWindow(game_window);
	SDL_Quit();
}
