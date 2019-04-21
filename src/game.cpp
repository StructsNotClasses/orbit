#include <iostream>
#include <assert.h>
#include <SDL2/SDL_ttf.h>
#include "game.h" 
#include "helpers.h"

bool Game::init(double g_x, double g_y, double G) {
  count=0;
  m_G=G;
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
  if(TTF_Init() < 0) return false;

	//create main window
	game_window = SDL_CreateWindow("yow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	if(game_window == NULL) return false;

	//create renderer and set draw color
	renderer = SDL_CreateRenderer(game_window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//render starting frame
	SDL_RenderPresent(renderer);

	//create player
	player = new Player("assets/ship_frames/none.png", (SCREEN_WIDTH/2+400), (SCREEN_HEIGHT/2-400), renderer, 1, g_x, g_y);

	//create star
	star = new Star("assets/sun.bmp", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), renderer, 1000);

  //create planets
  planets.push_back(new Planet(BARREN_ROCK, 170, 100, G, 500, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 0));
  planets.push_back(new Planet(BARREN_ROCK, 250, 100, G, 400, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 1));
  //planets.push_back(new Planet(BARREN_ROCK, 271, 100, 10, 600, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 0));
  //planets.push_back(new Planet(BARREN_ROCK, 271, 100, 10, 700, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 1));

  //check planets
  for(const Planet* planet : planets) {
    assert(planet && "failed to intialize a planet");
  }

  //create fuelbar
  fuel_bar = new FuelBar(SCREEN_WIDTH/2-600, SCREEN_HEIGHT-45, 1000, 1200, 40, renderer);


	return true;
}

void Game::update() {
  //overflow, though unlikely, could occur
  if(count<0)count=0;
  count+=1;

  //apply player movement
  if(!fuel_bar->isEmpty()) {
    if(w_pressed) {
      player->accelerateByAngle(player->m_angle, .10);
      fuel_bar->update(-1);
    }
    if(s_pressed) {
      player->accelerateByAngle(player->m_angle, -.10);
      fuel_bar->update(-1);
    }
    if(a_pressed) {
      player->accelerateSpin(-.10);
      fuel_bar->update(-1);
    }
    if(d_pressed) {
      player->accelerateSpin(.10);
      fuel_bar->update(-1);
    }
  }
  std::cout << "angle is " << player->m_angle << "\n";

	//animate sun
	star->update();

  //update planets
  for(Planet* current_planet : planets) {
    current_planet->pullTowardsObject(star, m_G);
    current_planet->pullTowardsObject(player,m_G);
    /*for(Planet* other_current_planet : planets) {
      if(!(current_planet == other_current_planet)) {
        current_planet->pullTowardsObject(other_current_planet,m_G);
      }
    }*/
    current_planet->update();
  }

  //update player
  player->pullTowardsObject(star, m_G);
  for(Planet* current_planet : planets) {
    player->pullTowardsObject(current_planet, m_G);
  }

	player->update();

	//clear the window
	if(SDL_RenderClear(renderer)) std::cout << SDL_GetError();

	//background image
	//
	//rendercopy the star
	star->render(renderer, count);

  //rendercopy the planets
  for(Planet* current_planet : planets) {
    current_planet->render(renderer);
  }

	//rendercopy the player
	player->render(renderer, w_pressed, s_pressed, fuel_bar->isEmpty(), count);

  //rendercopy the bar
  //SDL_FillRect(fuel_bar->bar_surface, NULL, SDL_MapRGB(fuel_bar->bar_surface->format, 055, 055, 055));
  fuel_bar->render(renderer);

	//render the changes
	SDL_RenderPresent(renderer);
}

bool Game::event(SDL_Event* event) {
	switch(event->type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was pressed\n";
			switch(event->key.keysym.sym) {
				case SDLK_w:
					w_pressed = 1;
					break;
			 	case SDLK_s:
					s_pressed = 1;
					break;
				case SDLK_a:
					a_pressed = 1;
					break;
				case SDLK_d:
					d_pressed = 1;
					break;
			}
			break;
		case SDL_KEYUP:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was released lol\n";
			switch(event->key.keysym.sym) {
				case SDLK_w:
					w_pressed=0;
					break;
				case SDLK_s:
					s_pressed=0;
					break;
				case SDLK_a:
					a_pressed=0;
					break;
				case SDLK_d:
					d_pressed=0;
					break;
			}
			break;
	}
	return true;
}


void Game::quit() {
  player->~Player();

  star->~Star();

  for(Planet* current_planet : planets) {
    current_planet->~Planet();
  }

	SDL_DestroyWindow(game_window);
  SDL_DestroyRenderer(renderer);
  TTF_Quit();
	SDL_Quit();
}
