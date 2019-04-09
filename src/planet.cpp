#include <assert.h>
#include <limits>
#include <cmath>
#include "object.h"
#include "planet.h"
#include "helpers.h"
#include "variables.h"


Planet::Planet(planetType type, int x_o, int y_o, SDL_Renderer* renderer, double mass, double v_x_o, double v_y_o)
  : Object(fileFromType(type), x_o, y_o, mass, renderer), m_srcrect(new SDL_Rect) {
  m_srcrect->w = 9;
  m_srcrect->h = 9;
  m_srcrect->x = 12;
  m_srcrect->y = 5;
  m_dstrect->w = 20;
  m_dstrect->h = 20;
  m_dstrect->x = x_o - m_srcrect->w/2;
  m_dstrect->y = y_o - m_srcrect->h/2;
  m_v_x = v_x_o;
  m_v_y = v_y_o;
}

//alternate constructor which takes the desired period of revolution and intializes the planet with the values to enable stable orbit with this period
Planet::Planet(planetType type, const int& angle_o, SDL_Renderer* renderer, const double& mass, const double& T_o /*ticks per revolution*/, double* tmp, const double& star_centerx, const double& star_centery)
  : tmp(getInitialValues(star_centerx, star_centery, angle_o, mass, g, T_o)) {
}

void Planet::update() {
	m_v_x += m_a_x;
	m_v_y += m_a_y;
	m_x += m_v_x;
	m_y += m_v_y;
	wrap(SCREEN_WIDTH, SCREEN_HEIGHT, &m_x, &m_y);
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;
}

void Planet::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, m_texture, m_srcrect, m_dstrect);
}

const char* Planet::fileFromType(planetType type) {
  switch(type) {
    case 0: return "assets/rock_planet.bmp";
    default: return "assets/rock_planet.bmp";
  }
}

//returns an array of values like {x_o, y_o, x_v_o, y_v_o}
double* Planet::getIntialValues(double star_c_x, double star_c_y, int angle, double mass, double g, double period, bool axis) {
  //get distance from sun's center
  const double& radius = std::cbrt((pow(period, 2)*g*mass)/(4*pow(PI, 2)));

  const double& velocityTangential = radius*(360/period);
}
