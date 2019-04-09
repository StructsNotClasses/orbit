#include <assert.h>
#include <iostream>
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
Planet::Planet(planetType type, const int& angle_o, const double& mass, double g, const double& T_o /*ticks per revolution*/, const double& star_centerx, const double& star_centery, const double& star_mass, SDL_Renderer* renderer)
  : Object(fileFromType(type), star_centerx, star_centery, star_mass, angle_o, mass, g, T_o, renderer), m_srcrect(new SDL_Rect) {
  m_srcrect->w = 9;
  m_srcrect->h = 9;
  std::cout << "skrrt\n";
  m_srcrect->x = 12;
  m_srcrect->y = 5;
  m_dstrect->w = 20;
  m_dstrect->h = 20;
  m_dstrect->x = m_x - m_srcrect->w/2;
  m_dstrect->y = m_y - m_srcrect->h/2;
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

//returns the array of values {x_o, y_o, x_v_o, y_v_o}
//negative period will reverse direction of rotation
/*
double* Planet::getInitialValues(double star_c_x, double star_c_y, int angle, double mass, double g, double period) {
  //get distance from sun's center
  const double& radius = std::cbrt((pow(period, 2)*g*mass)/(4*pow(M_PI, 2)));
  const double& velocity_tangential = radius*(360/period);

  if(angle<90) {
    return new double[4] {star_c_x+(180/M_PI)*sin(angle)*radius, star_c_y+(180/M_PI)*cos(angle)*radius, (180/M_PI)*cos(angle+90)*velocity_tangential, (180/M_PI)*sin(angle+90)*velocity_tangential};
  }
  else if(angle<180) {
    return new double[4] {star_c_x+(180/M_PI)*cos(angle)*radius, star_c_y+(180/M_PI)*sin(angle)*radius, (180/M_PI)*sin(angle+90)*velocity_tangential, (180/M_PI)*cos(angle+90)*velocity_tangential};
  }
  else if(angle<270) {
    return new double[4] {star_c_x+(180/M_PI)*sin(angle)*radius, star_c_y+(180/M_PI)*cos(angle)*radius, (180/M_PI)*cos(angle+90)*velocity_tangential, (180/M_PI)*sin(angle+90)*velocity_tangential};
  }
  else if(angle<360) {
    return new double[4] {star_c_x+(180/M_PI)*cos(angle)*radius, star_c_y+(180/M_PI)*sin(angle)*radius, (180/M_PI)*sin(angle-270)*velocity_tangential, (180/M_PI)*cos(angle-270)*velocity_tangential};
  }

  assert((0)&&"The angle is probably either negative or > 360, which is weird");
}
*/
