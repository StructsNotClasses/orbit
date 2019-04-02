#include "star.h"
#include "helpers.h"
#include <SDL2/SDL.h>
#include <assert.h>
Star::Star(const char* image_file, const char* image_file2, int x, int y, SDL_Renderer* renderer, double mass)
		: Object(image_file, x, y, mass, renderer), frame{0} {
	m_dstrect->w = 50;
	m_dstrect->h = 50;
	m_dstrect->x = m_x - 25;
	m_dstrect->y = m_y - 25;
	SDL_Surface* tmpsurf = surfaceFromBMP(image_file2);
	assert(tmpsurf && "Check image file, couldn't create");
	m_texture2 = SDL_CreateTextureFromSurface(renderer, tmpsurf);
	assert(m_texture2 && "couldn't create texture");

	SDL_FreeSurface(tmpsurf);
}
	
void Star::update() {
	frame=!frame;
}
	
void Star::render(SDL_Renderer* renderer) {
	if(frame) SDL_RenderCopy(renderer, m_texture, NULL, m_dstrect);
	else SDL_RenderCopy(renderer, m_texture2, NULL, m_dstrect);
}

