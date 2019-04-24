#include "object.h"
#include "player.h"
#include "helpers.h"
#include "game.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <limits>
Player::Player(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass, double g_x, double g_y) 
		: Object(image_file, x, y, mass, renderer), m_srcrect{new SDL_Rect} {

	forward1 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/ship_frames/only_forward1.png"));
  assert(forward1 && "couldn't load f1");

	forward2 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/ship_frames/only_forward2.png"));
  assert(forward2 && "couldn't load f2");

	backward1 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/ship_frames/only_backward1.png"));
  assert(backward1 && "couldn't load b1");

	backward2 = SDL_CreateTextureFromSurface(renderer, surfaceFromFile("assets/ship_frames/only_backward2.png"));
  assert(backward2 && "couldn't load b2");


	m_srcrect->w = 12;
	m_srcrect->h = 20;
	m_srcrect->x = 4;
	m_srcrect->y = 2; m_dstrect->w = 20;
	m_dstrect->h = 30;
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;
	m_a_x = g_x;
	m_a_y = g_y;

  m_angular_velocity = 0;
  m_center = new SDL_Point{10, 10};

}

//will return 1 if the player is out of bounds and the timer ended
bool Player::update() {
  //update the angle, ensure it stays within the 360 degree limit for convenience
  m_angle += m_angular_velocity;
  if(m_angle>=360) m_angle-=360;
  if(m_angle<0) m_angle+=360;

  //update velocities based on (constant) acceleration
	m_v_x += m_a_x;
	m_v_y += m_a_y;

  //update position based on velocity
	m_x += m_v_x;
	m_y += m_v_y;

  //gameEndWrap returns 1 if out of bounds
  if(endgame_active) if(gameEndWrap(SCREEN_WIDTH, SCREEN_HEIGHT, 5, &m_x, &m_y)) return 1;

  wrap(SCREEN_WIDTH, SCREEN_HEIGHT, &m_x, &m_y);

  //make the renderering rect reflect position changes
	m_dstrect->x = m_x;
	m_dstrect->y = m_y;

  return 0;
}

void Player::accelerate(double x, double y) {
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

void Player::accelerateSpin(double magnitude) {
  m_angular_velocity += magnitude;
}

void Player::accelerateByAngle(double angle, double magnitude) {
  std::cout << "angle is " << angle << "\n";
  //set starting coordinates and velocity based on angle
  if(angle<=90) {
    std::cout << "quadrant 1\n";
    m_v_x += sin(angle*(M_PI/180)) * magnitude;
    m_v_y -= cos(angle*(M_PI/180)) * magnitude;
    std::cout << "x: " << cos(angle*(M_PI/180)) * magnitude << "\n";
    std::cout << "y: " << sin(angle*(M_PI/180)) * magnitude << "\n";
  }
  else if(angle<=180) {
    std::cout << "quadrant 2\n";
    m_v_x += cos((angle-90)*(M_PI/180)) * magnitude;
    m_v_y += sin((angle-90)*(M_PI/180)) * magnitude;
  }
  else if(angle<=270) {
    std::cout << "quadrant 3\n";
    m_v_x -= sin((angle-180)*(M_PI/180)) * magnitude;
    m_v_y += cos((angle-180)*(M_PI/180)) * magnitude;
  }
  else {
    std::cout << "quadrant 4\n";
    m_v_x -= cos((angle-270)*(M_PI/180)) * magnitude;
    m_v_y -= sin((angle-270)*(M_PI/180)) * magnitude;
    std::cout << "x: " << cos((angle-270)*(M_PI/180)) * magnitude << "\n";
    std::cout << "y: " << sin((angle-270)*(M_PI/180)) * magnitude << "\n";
  }
  std::cout << "vx, vy: " << m_v_x << ", " << m_v_y << "\n";
}


void Player::render(SDL_Renderer* renderer, bool &w_pressed, bool &s_pressed, const bool& is_empty, int count) {
  //put count between 0 and 9 (inclusive)
  count%=10;

  std::cout << w_pressed << "," << s_pressed << "\n";
  //forward animation
  if(w_pressed && !s_pressed && !is_empty) {
    if(count<5)
	    SDL_RenderCopyEx(renderer, forward1, m_srcrect, m_dstrect, m_angle, m_center, SDL_FLIP_NONE);
    else
	    SDL_RenderCopyEx(renderer, forward2, m_srcrect, m_dstrect, m_angle, m_center, SDL_FLIP_NONE);
  }

  //backwards animation
  else if(s_pressed && !w_pressed && !is_empty) {
    if(count<5)
	    SDL_RenderCopyEx(renderer, backward1, m_srcrect, m_dstrect, m_angle, m_center, SDL_FLIP_NONE);
    else
	    SDL_RenderCopyEx(renderer, backward2, m_srcrect, m_dstrect, m_angle, m_center, SDL_FLIP_NONE);
  }

  else {
	  SDL_RenderCopyEx(renderer, m_texture, m_srcrect, m_dstrect, m_angle, m_center, SDL_FLIP_NONE);
  }
  std::cout << "\n";
}

Player::~Player() {
  //delete members
  //m_srcrect->~SDL_Rect();
  Object::~Object();
}
