#include "game.h" 
bool Game::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	
	game_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN );

	if(game_window == NULL) return false;

	screen = SDL_GetWindowSurface(game_window);

	if(screen == NULL) return false;
	
	SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) ); 

	return true;
}

void Game::update() {
	SDL_UpdateWindowSurface(game_window);
}

bool Game::event(SDL_Event* event) {
	if(event->type == SDL_QUIT)
		return false;

	return true;
}
	

void Game::quit() {
	SDL_DestroyWindow(game_window);
	SDL_Quit();
}
