#include <assert.h>
#include "timer.h"

Timer::Timer(int ptsize, int starting_time, const char* font_file) : font(TTF_OpenFont(font_file, ptsize)), m_starting_time(starting_time) {
  assert(font && "could not load font, file is: " && font_file);
}

void Timer::update(int count) {
  //account for 60fps, the int handles the decimal
  count = count/60;
  count = m_starting_time - count;
}
