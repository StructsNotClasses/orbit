#include <assert.h>
#include <limits>
#include <iostream>
#include "object.h"
#include "helpers.h"
Object::Object(const char* image_file, int x, int y, double mass, SDL_Renderer* renderer) 
		: m_x(x), m_y(y), m_m{mass}, m_a_x{0}, m_a_y{0} {
	m_surface = surfaceFromFile(image_file);
	assert(m_surface && "Check image file, couldn't create");
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	assert(m_texture && "couldn't create texture");
	m_dstrect = new SDL_Rect();
	assert(m_dstrect && "couldn't create dstrect");
	m_v_x=0;
	m_v_y=0;
}

Object::Object(const char* image_file, double star_centerx, double star_centery, double star_mass, double angle, double mass, double g, double radius, SDL_Renderer* renderer)
  : m_dstrect(new SDL_Rect), m_m(mass), m_a_x(0), m_a_y(0) {
  //get period of orbit
  //const double& T_o = 2*M_PI*(std::sqrt((radius*radius*radius)/(g*star_mass)));
  //const double& velocity_tangential = radius*(360/period); //good
  const double& velocity_tangential = std::sqrt(g*star_mass/radius);
  std::cout << " radius " << radius << " vt " << velocity_tangential << '\n';
  std::cout << "xstar " << star_centerx << " ystar " << star_centery << "\n";
  std::cout << "angle " << angle << "\n";

  //set starting coordinates and velocity based on angle
  if(angle<=90) {
    m_x = star_centerx+sin((angle)*M_PI/180)*radius;
    m_y = star_centery-cos((angle)*M_PI/180)*radius;
    m_v_x = -1 * sin((angle+90)*M_PI/180)*velocity_tangential;
    m_v_y = cos((angle+90)*M_PI/180)*velocity_tangential;
  }
  else if(angle<=180) {
    m_x = star_centerx+cos((angle-90)*M_PI/180)*radius;
    m_y = star_centery+sin((angle-90)*(M_PI/180))*radius;
    m_v_x = -1 * cos((angle)*M_PI/180)*velocity_tangential;
    m_v_y = -1 * sin((angle)*M_PI/180)*velocity_tangential;
  }
  else if(angle<=270) {
    m_x = star_centerx-sin((angle-180)*M_PI/180)*radius;
    m_y = star_centery+cos((angle-180)*(M_PI/180))*radius;
    m_v_x = sin((angle-90)*M_PI/180)*velocity_tangential;
    m_v_y = -1 * cos((angle-90)*M_PI/180)*velocity_tangential;
  }
  else {
    m_x = star_centerx-cos((angle-270)*M_PI/180)*radius;
    m_y = star_centery-sin((angle-270)*(M_PI/180))*radius;
    m_v_x = cos((angle-180)*M_PI/180)*velocity_tangential;
    m_v_y = sin((angle-180)*M_PI/180)*velocity_tangential;
  }

	m_surface = surfaceFromFile(image_file);
  m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	assert(m_surface && "couldn't create texture");
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

Object::~Object() {
  //delete members
  //SDL_DestroyTexture(m_texture);
  //SDL_FreeSurface(m_surface);
  //delete m_dstrect;
}
