#include "object.h"

class Player : public Object {
	public:
		Player(const char* image_file); 

		void update();
};

