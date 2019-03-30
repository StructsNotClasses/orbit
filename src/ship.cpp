#include "ship.h"
#include "helpers.h"
Player::Player(const char* image_file) {
	m_surface = surfaceFromBMP(image_file);
}
