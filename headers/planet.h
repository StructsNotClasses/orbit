#pragma once
#include "object.h"

enum planetType {
	BARREN_ROCK,
};

class Planet : public Object {
	public:
		Planet(planetType type, int x_o, int y_o, SDL_Renderer* renderer, double mass, double v_x_o, double v_y_o);
		Planet(planetType type, int angle_o, SDL_Renderer* renderer, double mass, double T_o);

	private:
		planetType m_type;
		double m_T_intial;
};
