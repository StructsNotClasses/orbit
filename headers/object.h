#pragma once
#include <SDL2/SDL.h>
class Object {
	public:
		SDL_Surface* m_surface;

	private:
		double m_v_x;
		double m_v_y;
		double m_a_x;
		double m_a_y;
		double mass;
};
