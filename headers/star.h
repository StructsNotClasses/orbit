#pragma once
#include "object.h"
#include <SDL2/SDL.h>
class Star : public Object {
	public: 
		Star(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass); 

		void update();

    void render(SDL_Renderer* renderer, int count);

		SDL_Texture* m_texture2{NULL};
    SDL_Texture* m_frame1{NULL};
    SDL_Texture* m_frame2{NULL};
    SDL_Texture* m_frame3{NULL};

    ~Star();

	private:
		bool frame;
};
