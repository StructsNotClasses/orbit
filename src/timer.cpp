#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "timer.h"
#include "helpers.h"

Timer::Timer(int ptsize, int starting_time, const char* font_file, SDL_Renderer* renderer) : m_font(TTF_OpenFontIndex(font_file, ptsize, 0)), m_surface(new SDL_Surface), m_starting_time(starting_time), m_dstrect(new SDL_Rect) {
  assert(m_font && "could not load font");
  assert(m_surface && "could not load timer surface");
  assert(m_dstrect && "could not load timer rect");

  current_time = new char[0];
  m_dstrect -> x = 5;
  m_dstrect -> y = 5;
  m_dstrect -> w = 100;
  m_dstrect -> h = 100;
}

void Timer::update(int count, SDL_Renderer* renderer) {
  //account for 60fps, assigning to an int handles the decimal
  count = count/60;

  count = m_starting_time - count;

  sprintf(current_time, "%d", count);

  SDL_Color tmp{255, 0, 0, 255};

  std::cout << TTF_FontHeight(m_font) << " lol \n";
  std::cout << count << " yeet \n";
  m_surface = TTF_RenderText_Solid(m_font, current_time, tmp);
  m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
}

void Timer::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, m_texture, NULL, m_dstrect);
}
