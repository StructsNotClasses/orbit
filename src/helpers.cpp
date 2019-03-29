#include "helpers.h"
#include <iostream>
SDL_Surface* surfaceFromBMP(const char* file) {
	SDL_Surface* return_surface{NULL};
	SDL_Surface* tmp_surface{NULL};

	tmp_surface = SDL_LoadBMP(file);
	if(tmp_surface == NULL) return NULL;
	std::cout << "whee\n";

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

bool drawToSurface(SDL_Surface* destination, SDL_Surface* source, int dx, int dy, int sx, int sy, int w, int h) {
	if(destination == NULL || source == NULL) return false;

	SDL_Rect destination_rect;
	destination_rect.x = dx;
	destination_rect.y = dy;

	SDL_Rect source_rect;
	source_rect.x = sx;
	source_rect.y = sy;

	source_rect.w = w;
	source_rect.h = h;

	SDL_BlitSurface(source, &source_rect, destination, &destination_rect);
	return true;
}


