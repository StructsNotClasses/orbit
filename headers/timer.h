#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Timer {
  public:
    Timer(int ptsize, int starting_time, const char* font_file);

    void update(int count);
    void render(int count);

    ~Timer();

    TTF_Font* m_font{NULL};
    SDL_Surface* m_surface{NULL};


  private:
    int m_starting_time;
    char* current_time;
};
