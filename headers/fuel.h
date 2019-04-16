#pragma once
#include <SDL2/SDL.h>

class FuelBar {
  public:
  FuelBar(int x, int y, double capacity, double starting_width, double height, SDL_Renderer* renderer);

    void update(double increment);
    void render(SDL_Renderer* renderer);

    ~FuelBar();

    SDL_Rect* bar{NULL};
    SDL_Surface* bar_surface{NULL};
    SDL_Texture* bar_texture{NULL};

  private:
    int m_x;
    int m_y;
    double m_capacity;
    double m_amount;
    double m_width;
    double m_height;
    double m_starting_width;
};
