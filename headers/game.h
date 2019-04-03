#pragma once
#include "player.h"
#include "star.h"
#include <SDL2/SDL.h>

class Game {
	public:
		//Game();
		//~Game();
	public:
		bool init(double g_x=0, double g_y=0);
		bool event(SDL_Event* event);
		void update();
		void quit();
	
		SDL_Texture* test{NULL};
		SDL_Rect* dstrect{nullptr};
		SDL_Window* game_window{NULL};
		SDL_Renderer* renderer{NULL};

		Player* player{nullptr};
		Star* star{nullptr};
		double* tmp;
	private:

		bool w_pressed{0};
		bool s_pressed{0};
		bool a_pressed{0};
		bool d_pressed{0};
};
	
