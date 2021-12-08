#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct RenderWindow {
    public:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Texture* LoadTexture(const char* imgPath){
            SDL_Texture* tex = NULL; 
            tex = IMG_LoadTexture(renderer, imgPath);

            if(tex == NULL)
                std::cout << "Failed to load texture" << SDL_GetError() << "\n";

            return tex;
        };
};
