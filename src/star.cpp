#include "star.h"
#include <SDL2/SDL.h>
Star::Star(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass)
		: Object(image_file, x, y, mass, renderer) {
	m_dstrect->w = 50;
	m_dstrect->h = 50;
	m_dstrect->x = m_x - 25;
	m_dstrect->y = m_y - 25;
}
	


