#pragma once
#include <SDL2/SDL.h>

struct RenderWindow {
    SDL_Renderer *renderer;
    SDL_Window *window;
};
