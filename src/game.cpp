#include <iostream>
#include "game.h" 
#include "helpers.h"
bool Game::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	
	//create main window
	game_window = SDL_CreateWindow("yow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );

	if(game_window == NULL) return false;

	//create renderer and set draw color
	renderer = SDL_CreateRenderer(game_window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//render starting frame
	SDL_RenderPresent(renderer);

	//create player
	player = new Player("assets/rocket.bmp", 10, 10, renderer);

	//create the player texture
	//test = SDL_CreateTextureFromSurface(renderer, surfaceFromBMP("assets/rocket.bmp"));
	//if(test == NULL) return false;

	//create the rect that controlles the player rendering location and size
	//dstrect = new SDL_Rect;
	//dstrect->x = x;
	//dstrect->y = y;
	//dstrect->w = 35;
	//dstrect->h = 35;

	return true;
}

void Game::update() {
	//change player accelerations
	player->update();

	//clear the window
	if(SDL_RenderClear(renderer)) std::cout << SDL_GetError();

	//background image
	
	//rendercopy the player
	//SDL_RenderCopy(renderer, player->m_texture, NULL, player->m_dstrect);
	player->render(renderer);

	//render the changes
	SDL_RenderPresent(renderer);
}

bool Game::event(SDL_Event* event) {
	switch(event->type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was pressed\n";
			switch(event->key.keysym.sym) {
				case SDLK_w: 
					if(!w_pressed) w_pressed = 1;
					break;
			 	case SDLK_s: 
					if(!s_pressed) s_pressed = 1;
					break;
				case SDLK_a:
					if(!a_pressed) a_pressed = 1;
					break;
				case SDLK_d:
					if(!d_pressed) d_pressed = 1;
					break;
			}
			break;
		case SDL_KEYUP:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was released lol\n";
			switch(event->key.keysym.sym) {
				case SDLK_w:
					if(w_pressed) w_pressed=0;
					break;
				case SDLK_s:
					if(s_pressed) s_pressed=0;
					break;
				case SDLK_a:
					if(a_pressed) a_pressed=0;
				case SDLK_d:
					if(d_pressed) d_pressed=0;
			}
			break;
	}
	if(w_pressed) player->accelerate(0, -.25);
	if(s_pressed) player->accelerate(0, .25);
	if(a_pressed) player->accelerate(-.25, 0);
	if(d_pressed) player->accelerate(.25, 0);
	return true;
}
	

void Game::quit() {
	//SDL_FreeSurface(screen);
	SDL_DestroyTexture(test);
	SDL_DestroyWindow(game_window);
	SDL_Quit();
}
