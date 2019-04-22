#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "timer.h"
#include "helpers.h"

Timer::Timer(int ptsize, int starting_time, const char* font_file, SDL_Renderer* renderer) : m_font(TTF_OpenFontIndex(font_file, ptsize, 0)), m_surface(new SDL_Surface), m_starting_time(starting_time) {
  std::cout << TTF_WasInit() << "\n";
  assert(m_font && "could not load font");
  current_time = new char[0];
  m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
}

void Timer::update(int count) {
  //account for 60fps, assigning to an int handles the decimal
  count = count/60;

  count = m_starting_time - count;

  sprintf(current_time, "%d", count);

  SDL_Color tmp{0, 0, 0, 255};

  m_surface = TTF_RenderText_Solid(m_font, current_time, tmp);
}

void Timer::render(SDL_Renderer* renderer) {
  //SDL_RenderCopy()
}
