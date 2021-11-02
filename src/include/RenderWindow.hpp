#pragma once
#include <SDL2/SDL.h>

struct RenderWindow{ // A class that stores both the SDL_Renderer and the SDL_Window in one place and makes them public by default
    SDL_Renderer *renderer;
    SDL_Window *window;
};