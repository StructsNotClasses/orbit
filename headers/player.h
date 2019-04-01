#include "object.h"

class Player : public Object {
	public:
		Player(const char* image_file, int x, int y, SDL_Renderer* renderer); 

		void update();

		void accelerate(double x, double y);

		void render(SDL_Renderer* renderer);
};

