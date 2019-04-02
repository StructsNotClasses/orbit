#pragma once
#include <SDL2/SDL.h>
class Object {
	public:
		Object(const char* image_file, int x, int y, SDL_Renderer* renderer);
		SDL_Surface* m_surface{NULL}; 
		SDL_Texture* m_texture{NULL};
		SDL_Rect* m_dstrect{NULL};

	protected:
		double m_x;
		double m_y;
		double m_v_x;
		double m_v_y;
		double m_a_x;
		double m_a_y;
		double mass;
};
