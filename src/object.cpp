#include <assert.h>
#include <limits>
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
