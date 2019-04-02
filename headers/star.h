#pragma once
#include "object.h"
#include <SDL2/SDL.h>
class Star : public Object {
	Star(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass); 

};
