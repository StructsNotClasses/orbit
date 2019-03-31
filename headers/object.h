#pragma once
#include <SDL2/SDL.h>
class Object {
	public:
		SDL_Surface* m_surface;
		SDL_Texture* m_texture;

	protected:
		double m_x;
		double m_y;
		double m_v_x;
		double m_v_y;
		double m_a_x;
		double m_a_y;
		double mass;
};
