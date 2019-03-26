#include <SDL2/SDL.h>
#include "capp.h"

bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
 	SDL_Window* Surf_Display;
	if((Surf_Display = SDL_CreateWindow("your fucking mom", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0 )) == NULL) {
		return false;
	}

	return true;
}

void CApp::OnEvent(SDL_Event* Event) {
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
}

void CApp::OnCleanup() {
}

