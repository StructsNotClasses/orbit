#pragma once
#include <SDL2/SDL.h>
class Object {
	public:
		Object(const char* image_file, int x, int y, double mass, SDL_Renderer* renderer);
    Object(const char* image_file, double star_centerx, double star_centery, double star_mass, double angle, double mass, double g, double period, SDL_Renderer* renderer);

    void accelerate(double x, double y);
    void pullTowardsObject(Object* object, const double g);

		SDL_Surface* m_surface{NULL}; 
		SDL_Texture* m_texture{NULL};
		SDL_Rect* m_dstrect{NULL};
		double getx() {return m_x;}
		double gety() {return m_y;}
    double getmass() {return m_m;}

    ~Object();

	protected:
    double m_x{0};
    double m_y{0};
    double m_v_x{0};
    double m_v_y{0};
    double m_m{0};
    double m_a_x{0};
    double m_a_y{0};
};
