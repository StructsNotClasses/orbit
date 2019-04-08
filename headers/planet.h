#pragma once
#include "object.h"

enum planetType {
	BARREN_ROCK,
};

class Planet : public Object {
	public:
    static const char* fileFromType(planetType type);

		Planet(planetType type, int x_o, int y_o, SDL_Renderer* renderer, double mass, double v_x_o, double v_y_o);

    static double* getInitialValues(double star_c_x, double star_c_y, int angle, double mass, double g, double period);

    Planet(planetType type, const int& angle_o, SDL_Renderer* renderer, const double& mass, double g, const double& T_o, const double& star_centerx, const double& star_centery);

    void accelerate(double x, double y);

    void update();
    void render(SDL_Renderer* renderer);

	private:
		planetType m_type;
		double m_T_intial;
    SDL_Rect* m_srcrect;
    //allows me to pass the data from a function into another thing
    double* tmp;
};
