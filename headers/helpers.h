#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <stdlib.h>

SDL_Surface* surfaceFromFile(const char* file);

bool drawToRenderer(SDL_Renderer* destination, SDL_Texture* source, int dx, int dy, int sx, int sy, int w, int h);

void wrap(int s_x, int s_y, double *o_x, double *o_y);

bool gameEndWrap(int s_x, int s_y,  int buffer, double *o_x, double *o_y);

double distance(double fx, double fy, double sx, double sy);

double gravitationalForce(double m1, double m2, double distance, const double g);

double* gravitationalAcceleration(double x1, double y1, double x2, double y2, double m1, double m2, const double g);

int lengthOfInteger(int intput);

int getRandomNumber(int min, int max);
