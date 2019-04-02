#include "helpers.h"
#include <cmath>
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

//rendercopies and handles rectangles, probably outdated or something but eh
bool drawToRenderer(SDL_Renderer* destination, SDL_Texture* source, int dx, int dy, int sx, int sy, int w, int h) {
	if(destination == NULL || source == NULL) return false;

	SDL_Rect destination_rect;
	destination_rect.x = dx;
	destination_rect.y = dy;

	SDL_Rect source_rect;
	source_rect.x = sx;
	source_rect.y = sy;

	source_rect.w = w;
	source_rect.h = h;

	SDL_RenderCopy(destination, source, &source_rect, &destination_rect);

	return true;
}

//wraps location of object "o" based on screen size "s"
constexpr int half_width = 17;
void wrap(int s_x, int s_y, double *o_x, double *o_y) {
	if(*o_x < -2 * half_width) *o_x = s_x;
	if(*o_x > s_x) *o_x = -2 * half_width;
	if(*o_y < -2 * half_width) *o_y = s_y;
	if(*o_y > s_y) *o_y = -2 * half_width;
}

//returns the distance between two objects
double distance(double fx, double fy, double sx, double sy) {
	return sqrt(pow(sx-fx, 2) + pow(sy-fy, 2));
}
