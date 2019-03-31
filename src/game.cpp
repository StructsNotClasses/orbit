#include <iostream>
#include "game.h" 
#include "helpers.h"
bool Game::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	
	game_window = SDL_CreateWindow("wheeeeeee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );

	if(game_window == NULL) return false;

	renderer = SDL_CreateRenderer(game_window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderPresent(renderer);

	screen = SDL_GetWindowSurface(game_window);

	if(screen == NULL) return false;
	
	test = SDL_CreateTextureFromSurface(renderer, surfaceFromBMP("assets/rocket.bmp"));
	if(test == NULL) return false;

	dstrect = new SDL_Rect;
	dstrect->x = x;
	dstrect->y = y;
	dstrect->w = 40;
	dstrect->h = 40;

	return true;
}

void Game::update() {
	//if(tes) tes = 0;
	//else tes = 1;

	//if(tes) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//else SDL_SetRenderDrawColor(renderer, 255, 255, 255 ,255);
	x+=vx;
	y+=vy;
	dstrect->x = x;
	dstrect->y = y;
	if(SDL_RenderClear(renderer)) std::cout << SDL_GetError();
	//drawToRenderer(renderer, test, x, y, 0, 0, 50, 50); 
	SDL_RenderCopy(renderer, test, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

bool Game::event(SDL_Event* event) {
	switch(event->type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << "was pressed\n";
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
			return true;
		case SDL_KEYUP:
			std::cout << "key was released lol\n";
			switch(event->key.keysym.sym) {
				case SDLK_w:
					if(w_pressed) w_pressed=0;
					break;
			}
				
			return true;
		default:
			return true;

	}
	if(w_pressed) vy-=1;
	if(s_pressed) vy+=1;
	if(a_pressed) vx-=1;
	if(d_pressed) vx+=1;
}
	

void Game::quit() {
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(test);
	SDL_DestroyWindow(game_window);
	SDL_Quit();
}
