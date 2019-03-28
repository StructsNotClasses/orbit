#pragma once
#include <SDL2/SDL.h>
SDL_Surface* surfaceFromBMP(const char* file);

bool drawToSurface(SDL_Surface* destination, SDL_Surface* source, int x, int y);

bool drawToSurface(SDL_Surface* destination, SDL_Surface* source, int dx, int dy, int sx, int sy, int w, int h);
