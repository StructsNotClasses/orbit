#include "helpers.h"
#include <assert.h>
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
constexpr int half_width = 3;
void wrap(int s_x, int s_y, double *o_x, double *o_y) {
	if(*o_x < -2 * half_width) *o_x = s_x;
	if(*o_x > s_x) *o_x = -2 * half_width;
	if(*o_y < -2 * half_width) *o_y = s_y;
	if(*o_y > s_y) *o_y = -2 * half_width;
}

//returns the distance between two objects, may not need this for a while
double distance(double fx, double fy, double sx, double sy) {
	return sqrt(pow(sx-fx, 2) + pow(sy-fy, 2));
}

//returns the force of gravity between two objects
double gravitationalForce(double m1, double m2, double distance, const double g) {
	return (m1*m2*g) / pow(distance, 2);
}

//returns the acceleration upon a single object by another
//takes locations and masses of both as well as a g-constant 
double* gravitationalAcceleration(double x1, double y1, double x2, double y2, double m1, double m2, const double g) {
	//calc force
	double force = gravitationalForce(m1, m2, distance(x1, x2, y1, y2), g);

	//determine quadrant
	int quadrent{-1};
	if((x2>=x1) && (y2<y1)) quadrent = 1;
	if((x2>x1) && (y2>=y1)) quadrent = 2;
	if((x2<=x1) && (y2>y1)) quadrent = 3;
	if((x2<x1) && (y2<=y1)) quadrent = 4;
	assert(!(quadrent==-1) && "Something is very wrong, perhaps a coordinate is null or something");

	//calc angle, the resulting angle is in radians and is from the distance line to the nearest axis in the counterclockwise direction
	//after angle calculated, use it to split the gravitational force into x and y components
	double angle{-361};
	switch(quadrent) {
		case 1: 
			angle=(atan((x2-x1)/(y1-y2))); 
			break;
		case 2: angle=(atan((y2-y1)/(x2-x1))); break;
		case 3: angle=(atan((x1-x2)/(y1-y2))); break;
		case 4: angle=(atan((y1-y2)/(x1-x2))); break;
	}

}
