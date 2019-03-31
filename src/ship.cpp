#include "ship.h"
#include "helpers.h"
Player::Player(const char* image_file, int x, int y, SDL_Renderer* renderer) {
	m_surface = surfaceFromBMP(image_file);
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	m_x = x;
	m_y = y;
}

void Player::update() {
	m_v_x += m_a_x;
	m_v_y += m_a_y;
	m_x += m_v_x;
	m_y += m_v_y;
}

//void Player::render(SDL_Surface* screen) {
//	SDL_BlitSurface(m_surface, NULL, screen, &destination_rect);
//}
