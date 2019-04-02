#pragma once
#include "object.h"
#include <SDL2/SDL.h>
class Star : public Object {
	public: 
		Star(const char* image_file, const char* image_file2, int x, int y, SDL_Renderer* renderer, double mass); 

		void update();

		void render(SDL_Renderer* renderer);

		SDL_Texture* m_texture2{NULL};

	private:
		bool frame;
};
