#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Timer {
  public:
    Timer(int ptsize, int starting_time, const char* font_file, SDL_Renderer* renderer);

    void update(int count, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

    ~Timer();

    TTF_Font* m_font;
    SDL_Surface* m_surface{NULL};
    SDL_Texture* m_texture{NULL};

    inline bool isEnded() {return timer_ended;}
    inline bool isNTen() {return negative_ten;}


  private:
    bool timer_ended{0};
    bool negative_ten{0};
    int m_starting_time;
    char* current_time;
    SDL_Rect* m_dstrect;
};
