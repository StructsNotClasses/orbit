#pragma once
#include <SDL2/SDL.h>
SDL_Surface* surfaceFromBMP(const char* file);

bool drawToRenderer(SDL_Renderer* destination, SDL_Texture* source, int dx, int dy, int sx, int sy, int w, int h);

void wrap(int s_x, int s_y, double *o_x, double *o_y);

double distance(double fx, double fy, double sx, double sy);

double* gravitationalAcceleration(double x1, double y1, double x2, double y2, double m1, double m2, const double g);
