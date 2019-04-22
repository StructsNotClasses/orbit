#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "player.h"
#include "star.h"
#include "planet.h"
#include "object.h"
#include "variables.h"
#include "fuel.h"
#include "timer.h"

class Game {
	public:
		//Game();
		//~Game();
	public:
    bool init(double g_x=0, double g_y=0, double G = 1);
		bool event(SDL_Event* event);
		void update();
		void quit();

		SDL_Window* game_window{NULL};
		SDL_Renderer* renderer{NULL};

		Player* player{nullptr};
		Star* star{nullptr};
    std::vector<Planet*> planets{nullptr};
    FuelBar* fuel_bar{nullptr};
    Timer* timer{nullptr};

    //an easy way to manage better animations
    int count;

	private:

		bool w_pressed{0};
		bool s_pressed{0};
		bool a_pressed{0};
		bool d_pressed{0};

    double m_G;
};

