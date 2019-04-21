#pragma once
#include "object.h"

class Player : public Object {
	public:
		Player(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass, double g_x=0, double g_y=0); 

		void update();

		void accelerate(double x, double y);
    void accelerateSpin(double magnitude);
    void accelerateByAngle(double angle, double magnitude);

    void render(SDL_Renderer* renderer, bool& w_pressed, bool& s_pressed, const bool& is_empty, int count);

    ~Player();

		SDL_Rect* m_srcrect{NULL};
    SDL_Point* m_center{NULL};
    double m_angle;
    double m_angular_velocity;
  private:
    SDL_Texture* forward1{NULL};
    SDL_Texture* forward2{NULL};
    SDL_Texture* backward1{NULL};
    SDL_Texture* backward2{NULL};
};

