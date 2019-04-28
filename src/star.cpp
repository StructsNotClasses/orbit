#include "star.h"
#include "helpers.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <iostream>
Star::Star(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass)
  : Object(image_file, x, y, mass, renderer) {
	m_dstrect->w = 50;
	m_dstrect->h = 50;
	m_dstrect->x = x - 25;
	m_dstrect->y = y - 25;

  m_m = mass;

  //init frames of animation
	m_frame1 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/sun_frames/sun1.png"));
	m_frame2 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/sun_frames/sun2.png"));
	m_frame3 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/sun_frames/sun3.png"));
}

void Star::render(SDL_Renderer* renderer, int count) {
  //reduce count to 0-29 (inclusive)
  count%=30;
  if(count<10) SDL_RenderCopy(renderer, m_frame1, NULL, m_dstrect);
  else if(count<20) SDL_RenderCopy(renderer, m_frame2, NULL, m_dstrect);
  else SDL_RenderCopy(renderer, m_frame3, NULL, m_dstrect);
}

Star::~Star() {
  //delete members
  SDL_DestroyTexture(m_texture2);
  Object::~Object();
}



