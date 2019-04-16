#include "fuel.h"
FuelBar::FuelBar(int x, int y, double capacity, double starting_width, double height, SDL_Renderer* renderer)
  : m_x(x), m_y(y), m_capacity(capacity), m_width(starting_width), m_height(height), m_starting_width(starting_width) {

  bar = new SDL_Rect;

  bar->x = m_x;
  bar->y = m_y;
  bar->w = starting_width;
  bar->h = height;

  bar_surface = new SDL_Surface;
  bar_texture = SDL_CreateTextureFromSurface(renderer, bar_surface);

  SDL_FillRect(bar_surface, bar, SDL_MapRGB(bar_surface->format, 0, 255, 0));
}

void FuelBar::update(double increment) {
  m_amount += increment;

  bar->w = m_starting_width * (m_amount/m_capacity);
}

void FuelBar::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, bar_texture, NULL, bar);
}

FuelBar::~FuelBar() {
  SDL_FreeSurface(bar_surface);
}
