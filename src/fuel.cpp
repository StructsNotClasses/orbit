#include <iostream>
#include <assert.h>
#include "fuel.h"
#include "helpers.h"

/*
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const uint32_t R_MASK = 0xff000000;
const uint32_t G_MASK = 0x00ff0000;
const uint32_t B_MASK = 0x0000ff00;
#else
const uint32_t R_MASK = 0x000000ff;
const uint32_t G_MASK = 0x0000ff00;
const uint32_t B_MASK = 0x00ff0000;
#endif
*/

FuelBar::FuelBar(int x, int y, double capacity, double starting_width, double height, SDL_Renderer* renderer)
  : m_x(x), m_y(y), m_capacity(capacity), m_amount(capacity), m_width(starting_width), m_height(height), m_starting_width(starting_width) {

  //create the bar's stuff 
  bar = new SDL_Rect;
  assert(bar && "couldn't initialize bar rectangle");

  bar->x = m_x;
  bar->y = m_y;
  bar->w = starting_width;
  bar->h = height;

  bar_surface = surfaceFromFile("assets/blank_image.png");
  assert(bar_surface && "couldn't intialize bar surface");

  bar_texture = SDL_CreateTextureFromSurface(renderer, bar_surface);
  assert(bar_texture && "couldn't intialize bar texture");

  //create the title stuff
  title_placement = new SDL_Rect;

  title_placement->w = bar->w/6;
  title_placement->h = bar->h;
  title_placement->x = bar->x+bar->w/2-title_placement->w/2;
  title_placement->y = bar->y;

  assert(title_placement && "couldn't initialize fuel-title rectangle");
  title_surface = surfaceFromFile("assets/misc_img/fuel_title.png");
  assert(title_surface && "couldn't intialize title texture");

  title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
  assert(title_surface && "couldn't initialize title texture");

}

void FuelBar::update(double increment) {
  m_amount += increment;
  //determine color by amount of fuel
  double rgbval = 255*m_amount/m_capacity;

  if(rgbval>0) SDL_SetTextureColorMod(bar_texture, 255-rgbval, rgbval, 0);
  std::cout << m_amount << "\n";

  bar->w = m_starting_width*(m_amount/m_capacity);

}

void FuelBar::render(SDL_Renderer* renderer) {
  //SDL_FillRect(bar_surface, bar, SDL_MapRGB(bar_surface->format, 0, 255, 0));
  SDL_RenderCopy(renderer, bar_texture, NULL, bar);
  SDL_RenderCopy(renderer, title_texture, NULL, title_placement);
}

FuelBar::~FuelBar() {
  SDL_FreeSurface(bar_surface);
}
