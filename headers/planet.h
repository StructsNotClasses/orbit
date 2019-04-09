#pragma once
#include "object.h"

enum planetType {
	BARREN_ROCK,
};

class Planet : public Object {
	public:
    static const char* fileFromType(planetType type);
  
		Planet(planetType type, int x_o, int y_o, SDL_Renderer* renderer, double mass, double v_x_o, double v_y_o);
		Planet(planetType type, int angle_o, SDL_Renderer* renderer, double mass, double T_o);

    void accelerate(double x, double y);

    void update();
    void render(SDL_Renderer* renderer);

	private:
		planetType m_type;
		double m_T_intial;
    SDL_Rect* m_srcrect;
};
