#pragma once
#include "player.h"
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
	
		SDL_Texture* test{NULL};
		SDL_Rect* dstrect{nullptr};
		SDL_Window* game_window{NULL};
		SDL_Renderer* renderer{NULL};

		Player* player{nullptr};
	private:
		int x{20};
		int y{50};
		double vx;
		double vy;

		bool w_pressed{0};
		bool s_pressed{0};
		bool a_pressed{0};
		bool d_pressed{0};
};
	
