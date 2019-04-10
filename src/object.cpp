#include <assert.h>
#include <limits>
#include <iostream>
#include "object.h"
#include "helpers.h"
Object::Object(const char* image_file, int x, int y, double mass, SDL_Renderer* renderer) 
		: m_x(x), m_y(y), m_m{mass}, m_a_x{0}, m_a_y{0} {
	m_surface = surfaceFromBMP(image_file);
	assert(m_surface && "Check image file, couldn't create");
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	assert(m_texture && "couldn't create texture");
	m_dstrect = new SDL_Rect();
	assert(m_dstrect && "couldn't create dstrect");
	m_v_x=0;
	m_v_y=0;
}

Object::Object(const char* image_file, double star_centerx, double star_centery, double star_mass, double angle, double mass, double g, double period, SDL_Renderer* renderer)
    : m_m(mass), m_a_x(0), m_a_y(0) {
  //get distance from sun's center
  const double& radius = std::cbrt((pow(period, 2)*g*star_mass)/(4*pow(M_PI, 2)));
  const double& velocity_tangential = .01 * radius*(2*M_PI/period);

  std::cout << "radius " << radius << " vt " << velocity_tangential << '\n';

  double* values;
  if(angle<90)
    values = new double[4] {star_centerx+(180/M_PI)*sin(angle)*radius, star_centery+(180/M_PI)*cos(angle)*radius, (180/M_PI)*cos(angle+90)*velocity_tangential, (180/M_PI)*sin(angle+90)*velocity_tangential};
  else if(angle<180)
    values = new double[4] {star_centerx+(180/M_PI)*cos(angle)*radius, star_centery+(180/M_PI)*sin(angle)*radius, (180/M_PI)*sin(angle+90)*velocity_tangential, (180/M_PI)*cos(angle+90)*velocity_tangential};
  else if(angle<270)
    values = new double[4] {star_centerx+(180/M_PI)*sin(angle)*radius, star_centery+(180/M_PI)*cos(angle)*radius, (180/M_PI)*cos(angle+90)*velocity_tangential, (180/M_PI)*sin(angle+90)*velocity_tangential};
  else
    values = new double[4] {star_centerx+(180/M_PI)*cos(angle)*radius, star_centery+(180/M_PI)*sin(angle)*radius, (180/M_PI)*sin(angle-270)*velocity_tangential, (180/M_PI)*cos(angle-270)*velocity_tangential};

  m_x = values[0];
  m_y = values[1];
  m_v_x = values[2];
  m_v_y = values[3];

	m_surface = surfaceFromBMP(image_file);
	assert(m_surface && "Check image file, couldn't create");
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	assert(m_texture && "couldn't create texture");
	m_dstrect = new SDL_Rect();
	assert(m_dstrect && "couldn't create dstrect");
}
void Object::accelerate(double x, double y) {
	if(x == std::numeric_limits<double>::infinity()) x = 0;
	if(x == -1 * std::numeric_limits<double>::infinity()) x = 0;
	if(y == std::numeric_limits<double>::infinity()) y = 0;
	if(y == -1 * std::numeric_limits<double>::infinity()) y = 0;
	//std::cout << "x acc: " << x << "\ny acc: " << y << '\n';
	m_v_x += x;
	//std::cout << m_v_x << " ";
	m_v_y += y;
	//std::cout << m_v_y << '\n';
}

void Object::pullTowardsObject(Object* object, const double g) {
  double* acc = gravitationalAcceleration(object->getx(), object->gety(), m_x, m_y, object->getmass(), m_m, g);
  accelerate(acc[0], acc[1]);
}
