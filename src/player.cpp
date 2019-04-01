#include "object.h"
#include "player.h"
#include "helpers.h"
Player::Player(const char* image_file, int x, int y, SDL_Renderer* renderer) : Object(image_file, x, y, renderer) {
	m_dstrect->w = 35;
	m_dstrect->h = 35;
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;
}

void Player::update() {
	m_v_x += m_a_x;
	m_v_y += m_a_y;
	m_x += m_v_x;
	m_y += m_v_y;
	wrap(640, 800, &m_x, &m_y);
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;
}

void Player::accelerate(double x, double y) {
	m_v_x += x;
	m_v_y += y;
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstrect);
}

//void Player::render(SDL_Surface* screen) {
//}
