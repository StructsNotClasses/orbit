#pragma once
#include <SDL2/SDL.h>
class Object {
	public:
		Object(const char* image_file, int x, int y, double mass, SDL_Renderer* renderer);

    void accelerate(double x, double y);
    void pullTowardsObject(Object* object, const double g);

		SDL_Surface* m_surface{NULL}; 
		SDL_Texture* m_texture{NULL};
		SDL_Rect* m_dstrect{NULL};
		double getx() {return m_x;}
		double gety() {return m_y;}
    double getmass() {return m_m;}

	protected:
		double m_x;
		double m_y;
		double m_v_x;
		double m_v_y;
		double m_m;
		double m_a_x;
		double m_a_y;
};
