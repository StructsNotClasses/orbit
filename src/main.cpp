#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
constexpr int SCREEN_WIDTH{640};
constexpr int SCREEN_HEIGHT{800};

void updateObjects() {
}

int main(int argc, char* args[]) {
	//create main window
	SDL_Window* window = NULL;

	SDL_Surface* screen = NULL;

	SDL_Surface* screen_image = SDL_LoadBMP("~/Coding/C++/orbit/assets/ship.bmp");

	assert(screen_image && "Image could not initialize");


 	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		std::cout <<  "SDL could not initialize! SDL_Error: %s\n" <<  SDL_GetError();
	}

	else { 
		//Create window 
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 

		if( window == NULL ) { 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}

		else { 
			//Get window surface 
			SDL_BlitSurface( screen_image, NULL, screen, NULL);
			//Update the surface 
			SDL_UpdateWindowSurface( window ); 
			//Wait two seconds 
			SDL_Delay( 2000 ); 
		} 
	}

	//Destroy window 
	SDL_DestroyWindow( window ); 

	//Quit SDL subsystems 
	SDL_Quit(); 

	return 0;  
	//update values
	//update position
	//render
}

