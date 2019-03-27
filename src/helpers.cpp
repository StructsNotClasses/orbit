#include "helpers.h"
SDL_Surface* surfaceFromBMP(const char* file) {
	SDL_Surface* return_surface{NULL};
	SDL_Surface* tmp_surface{NULL};

	tmp_surface = SDL_LoadBMP(file);
	if(return_surface == NULL) return NULL;

	return_surface = SDL_ConvertSurfaceFormat(tmp_surface, SDL_PIXELFORMAT_RGB555, 0);
	SDL_FreeSurface(tmp_surface);
	
	return return_surface;
}

bool drawToSurface(SDL_Surface* destination, SDL_Surface* source, int x, int y) {
	if(destination == NULL || source == NULL) return false;
	SDL_Rect destination_rect;
	destination_rect.x = x;
	destination_rect.y = y;

	SDL_BlitSurface(source, NULL, destination, &destination_rect);

	return true;
}
