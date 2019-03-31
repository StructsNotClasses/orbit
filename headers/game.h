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
	
		SDL_Surface* screen{NULL};
		SDL_Texture* test{NULL};
		SDL_Rect* dstrect{nullptr};
		SDL_Window* game_window{NULL};
		SDL_Renderer* renderer{NULL};
	private:
		bool tes{1};
		int x{20};
		int y{50};
		int vx;
		int vy;

		bool w_pressed{0};
		bool s_pressed{0};
		bool a_pressed{0};
		bool d_pressed{0};
};
	
