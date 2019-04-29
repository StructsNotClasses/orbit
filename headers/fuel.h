#pragma once
#include <SDL2/SDL.h>
#include "variables.h"

class FuelBar {
  public:
    FuelBar(int x, int y, double capacity, double starting_width, double height, SDL_Renderer* renderer);

    void fill() {m_amount = m_capacity;};
    void update(double increment);
    void render(SDL_Renderer* renderer);

    bool isEmpty() {return !(m_amount>0);};

    ~FuelBar();

    SDL_Rect* bar{NULL};
    SDL_Surface* bar_surface{NULL};
    SDL_Texture* bar_texture{NULL};
    SDL_Rect* title_placement{NULL};
    SDL_Surface* title_surface{NULL};
    SDL_Texture* title_texture{NULL};

  private:
    int m_x;
    int m_y;
    double m_capacity;
    double m_amount;
    double m_starting_width;
};
