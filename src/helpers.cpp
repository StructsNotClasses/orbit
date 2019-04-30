#include "helpers.h"
#include <assert.h>
#include <cmath>
#include <iostream>


SDL_Surface* surfaceFromFile(const char* file) {
	SDL_Surface* return_surface{NULL};
	//SDL_Surface* tmp_surface{NULL};

	return_surface = IMG_Load(file);
	//if(tmp_surface == NULL) return NULL;

  /*
	return_surface = SDL_ConvertSurfaceFormat(tmp_surface, SDL_PIXELFORMAT_RGBA5551, 0);
	SDL_FreeSurface(tmp_surface);
  */
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

bool gameEndWrap(int s_x, int s_y, int buffer, double *o_x, double *o_y) {
	if(*o_x < -2 * half_width+buffer) return 1;
	if(*o_x > s_x-buffer)             return 1;
	if(*o_y < -2 * half_width+buffer) return 1;
	if(*o_y > s_y-buffer)             return 1;

  return 0;
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
//takes locations and masses of both as well as a g-constant, 1 is the object pulling 2
double* gravitationalAcceleration(double x1, double y1, double x2, double y2, double m1, double m2, const double g) {
	//calc force
	const double &force = gravitationalForce(m1, m2, distance(x1, y1, x2, y2), g)/m2;

	//determine quadrant
	int quadrant{-1};
	if((x2>=x1) && (y2<y1)) quadrant = 1;
	if((x2>x1) && (y2>=y1)) quadrant = 2;
	if((x2<=x1) && (y2>y1)) quadrant = 3;
	if((x2<x1) && (y2<=y1)) quadrant = 4;
	if(quadrant==-1) return new double[2] {0,0};

	//calc angle, the resulting angle is in radians and is from the distance line to the nearest axis in the counterclockwise direction
	//after angle calculated, use it to split the gravitational force into x and y components
	//returns a double* with x as first index and y as second index
	double angle{0};
	switch(quadrant) {
		case 1:
			angle=(atan((x2-x1)/(y1-y2)));
			return new double[2] {-1*(sin(angle)*force),cos(angle)*force};
		case 2:
			angle=(atan((y2-y1)/(x2-x1)));
			return new double[2] {-1*(cos(angle)*force),-1*(sin(angle)*force)};
		case 3:
			angle=(atan((x2-x1)/(y1-y2)));
			return new double[2] {sin(angle)*force,-1*(cos(angle)*force)};
		case 4:
			angle=(atan((y1-y2)/(x1-x2)));
			return new double[2] {cos(angle)*force,sin(angle)*force};
		default:
			return 0;
	}
}

int lengthOfInteger(int intput) {
  int digits{0};
  while(intput) {
    intput/=10;
    digits+=1;
  }
  return digits;
}

int getRandomNumber(int min, int max) {
  int returnval = rand() % ((min + max)?(min+max):1);
  if(returnval == 0) return min;
  else return returnval;
}
