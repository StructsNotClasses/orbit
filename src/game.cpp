#include <iostream>
#include <assert.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "helpers.h"
#include "timer.h"

bool Game::init(double g_x, double g_y, double G)
{
    count = 0;
    m_G = G;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    if (TTF_Init() < 0)
        return false;

    //create main window
    game_window = SDL_CreateWindow("orbit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (game_window == NULL)
        return false;

    //create renderer and set draw color
    renderer = SDL_CreateRenderer(game_window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //render starting frame
    SDL_RenderPresent(renderer);

    //create background
    SDL_Surface *tmp = surfaceFromFile("assets/blank_image.png");
    background_rect = new SDL_Rect;
    background_rect->x = 5;
    background_rect->y = 5;
    background_rect->w = SCREEN_WIDTH - 10;
    background_rect->h = SCREEN_HEIGHT - 10;

    black_background = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_SetTextureColorMod(black_background, 0, 0, 0);

    SDL_FreeSurface(tmp);

    //create player
    player = new Player("assets/ship_frames/none.png", (SCREEN_WIDTH / 2 + 400), (SCREEN_HEIGHT / 2 - 400), renderer, 1, g_x, g_y);
    assert(player && "player couldn't intialize");

    //create star
    star = new Star("assets/sun.bmp", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), renderer, 1000);
    assert(star && "star couldn't intialize");

    //create planets
    planets.push_back(new Planet(BARREN_ROCK, 170, 100, G, 500, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, renderer, 0));
    planets.push_back(new Planet(BARREN_ROCK, 250, 100, G, 400, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, renderer, 1));
    //planets.push_back(new Planet(BARREN_ROCK, 271, 100, G, 600, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 0));
    //std::cout << planets[2] << "\n";
    //planets.push_back(new Planet(BARREN_ROCK, 271, 100, G, 700, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 1));
    //std::cout << planets[3] << "\n";

    //check planets
    for (const Planet *planet : planets)
    {
        assert(planet->m_srcrect && "failed to intialize a planet");
    }

    //create fuelbar
    fuel_bar = new FuelBar(SCREEN_WIDTH / 2 - 600, SCREEN_HEIGHT - 45, 1000, 1200, 40, renderer);

    //create timer
    timer = new Timer(28, 10, "/usr/share/fonts/TTF/FiraCode-Medium.ttf", renderer);

    return true;
}

void Game::newSystem(double g_x, double g_y)
{
    //m_G will be the seed
    m_G = getRandomNumber(2, 8);
    count = 0;

    //set draw color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //reset star
    star->~Star();
    star = new Star("assets/sun.bmp", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), renderer, 1000);
    assert(star && "star couldn't reset");

    //clear planets
    for (Planet *current_planet : planets)
    {
        current_planet->~Planet();
    }
    planets.clear();

    //create planets
    bool counter_clockwise{static_cast<bool>(getRandomNumber(0, 2))};
    planets.push_back(new Planet(BARREN_ROCK, m_G * 50 + getRandomNumber(-50, 150), 100, m_G, getRandomNumber(100, 500), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, renderer, counter_clockwise));
    planets.push_back(new Planet(BARREN_ROCK, m_G * 50 + getRandomNumber(-50, 150), 100, m_G, getRandomNumber(100, 500), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1000, renderer, getRandomNumber(0, 2) * counter_clockwise));
    //planets.push_back(new Planet(BARREN_ROCK, 271, 100, G, 600, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 0));
    //std::cout << planets[2] << "\n";
    //planets.push_back(new Planet(BARREN_ROCK, 271, 100, G, 700, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1000, renderer, 1));
    //std::cout << planets[3] << "\n";

    //check new planets
    for (const Planet *planet : planets)
    {
        assert(planet->m_srcrect && "failed to reset a planet");
    }

    //reset player based on planet mogevement
    int starting_velocity{static_cast<int>(m_G) * getRandomNumber(1, 2)};
    if (counter_clockwise)
        player->resetValues(1360, 590, 0, starting_velocity);
    else
        player->resetValues(1360, 590, 0, -starting_velocity);

    //clear fuelbar
    fuel_bar->~FuelBar();

    //create fuelbar
    fuel_bar = new FuelBar(SCREEN_WIDTH / 2 - 600, SCREEN_HEIGHT - 45, starting_velocity * 1.25, 1200, 40, renderer);

    //clear timer
    timer->~Timer();

    //create timer
    timer = new Timer(28, starting_velocity * 2, "/usr/share/fonts/TTF/FiraCode-Medium.ttf", renderer);
    std::cout << "velocity: " << starting_velocity << "\n";
    for (int i{0}; i < 10; i++)
        std::cout << getRandomNumber(1, 2) << "\n";
}

void Game::update(bool &running)
{
    //overflow, though unlikely, could occur
    if (count < 0)
        count = 0;
    count += 1;

    //apply player movement
    if (!fuel_bar->isEmpty())
    {
        if (w_pressed)
        {
            player->accelerateByAngle(*(player->getAngle()), .20);
            fuel_bar->update(-.25);
        }
        if (s_pressed)
        {
            player->accelerateByAngle(*(player->getAngle()), -.20);
            fuel_bar->update(-.25);
        }
        if (a_pressed)
        {
            player->accelerateSpin(-.20);
            fuel_bar->update(-.0);
        }
        if (d_pressed)
        {
            player->accelerateSpin(.20);
            fuel_bar->update(-.0);
        }
    }

    //update planets
    for (Planet *current_planet : planets)
    {
        current_planet->pullTowardsObject(star, m_G);
        current_planet->pullTowardsObject(player, m_G);
        /*
    for(Planet* other_current_planet : planets) {
      if(!(current_planet == other_current_planet))
        current_planet->pullTowardsObject(other_current_planet,m_G);
    }
    */
        current_planet->update();
    }

    //set "endgame mode"
    if (timer->isEnded())
    {
        player->setEndgame(1);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    if (timer->isNTen())
    {
        for (int i = 0; i < 20; i++)
            std::cout << "\n";
        std::cout << "You won! Congratulations.\n";
        for (int i = 0; i < 2; i++)
            std::cout << "\n";
        running = 0;
    }

    //update player
    player->pullTowardsObject(star, m_G);
    for (Planet *current_planet : planets)
    {
        player->pullTowardsObject(current_planet, m_G);
    }

    if (player->update())
        endSession();

    //update the timer
    timer->update(count, renderer);

    //clear the window
    if (SDL_RenderClear(renderer))
        std::cout << SDL_GetError();

    //rendercopy the background
    SDL_RenderCopy(renderer, black_background, NULL, background_rect);

    //rendercopy the timer
    timer->render(renderer);

    //background image
    //
    //rendercopy the star
    star->render(renderer, count);

    //rendercopy the planets
    for (Planet *current_planet : planets)
    {
        if (current_planet)
            current_planet->render(renderer);
    }

    //rendercopy the player
    player->render(renderer, w_pressed, s_pressed, fuel_bar->isEmpty(), count);

    //rendercopy the bar
    //SDL_FillRect(fuel_bar->bar_surface, NULL, SDL_MapRGB(fuel_bar->bar_surface->format, 055, 055, 055));
    fuel_bar->render(renderer);

    //render the changes
    SDL_RenderPresent(renderer);
}

bool Game::event(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        return false;
    case SDL_KEYDOWN:
        std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was pressed\n";
        switch (event->key.keysym.sym)
        {
        case SDLK_w:
            w_pressed = 1;
            break;
        case SDLK_s:
            s_pressed = 1;
            break;
        case SDLK_a:
            a_pressed = 1;
            break;
        case SDLK_d:
            d_pressed = 1;
            break;

        case SDLK_r:
            newSystem(0, 0);
        }
        break;
    case SDL_KEYUP:
        std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was released\n";
        switch (event->key.keysym.sym)
        {
        case SDLK_w:
            w_pressed = 0;
            break;
        case SDLK_s:
            s_pressed = 0;
            break;
        case SDLK_a:
            a_pressed = 0;
            break;
        case SDLK_d:
            d_pressed = 0;
            break;
        }
        break;
    }
    return true;
}

void Game::endSession()
{
    newSystem(0, 0);
}

void Game::quit()
{
    player->~Player();

    star->~Star();

    for (Planet *current_planet : planets)
    {
        current_planet->~Planet();
    }

    fuel_bar->~FuelBar();

    timer->~Timer();

    SDL_DestroyWindow(game_window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}
