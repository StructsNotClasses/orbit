#include "object.h"
#include "player.h"
#include "helpers.h"
#include "game.h"
#include <iostream>
#include <limits>
Player::Player(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass, double g_x, double g_y) 
		: Object(image_file, x, y, mass, renderer), m_srcrect{new SDL_Rect} {
	m_srcrect->w = 6;
	m_srcrect->h = 10;
	m_srcrect->x = 11;
	m_srcrect->y = 3;
	m_dstrect->w = 10;
	m_dstrect->h = 20;
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;
	m_a_x = g_x;
	m_a_y = g_y;
}

void Player::update() {
	m_v_x += m_a_x;
	m_v_y += m_a_y;
	m_x += m_v_x;
	m_y += m_v_y;
	wrap(SCREEN_WIDTH, SCREEN_HEIGHT, &m_x, &m_y);
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;
}

void Player::accelerate(double x, double y) {
	if(x == std::numeric_limits<double>::infinity()) x = 0;
	if(x == -1 * std::numeric_limits<double>::infinity()) x = 0;
	if(y == std::numeric_limits<double>::infinity()) y = 0;
	if(y == -1 * std::numeric_limits<double>::infinity()) y = 0;
	std::cout << "x acc: " << x << "\ny acc: " << y << '\n';
	m_v_x += x;
	std::cout << m_v_x << " ";
	m_v_y += y;
	std::cout << m_v_y << '\n';
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, m_srcrect, m_dstrect);
}

//void Player::render(SDL_Surface* screen) {
//}
