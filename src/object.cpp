#include <assert.h>
#include "object.h"
#include "helpers.h"
Object::Object(const char* image_file, int x, int y, SDL_Renderer* renderer) : m_x(x), m_y(y), m_a_x{0}, m_a_y{0} {
	m_surface = surfaceFromBMP(image_file);
	assert(m_surface && "Check image file, couldn't create");
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	assert(m_texture && "couldn't create texture");
	m_dstrect = new SDL_Rect();
	assert(m_dstrect && "couldn't create dstrect");
}

