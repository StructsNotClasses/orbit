#include "object.h"

class Player : public Object {
	public:
		Player(const char* image_file, int x, int y, SDL_Renderer* renderer, double mass, double g_x=0, double g_y=0); 

		void update();

		void accelerate(double x, double y);

		void render(SDL_Renderer* renderer);

		SDL_Rect* m_srcrect{NULL};
};

