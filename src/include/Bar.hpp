#pragma once
#include <SDL2/SDL.h>
#include <Vector2.hpp>
#include <iostream>

struct Bar {
    SDL_Color bgColor;
    SDL_Color fillColor;
    SDL_Rect bgBar;
    SDL_Rect valueBar;
    Bar(Vector2 origin, float height, float width, SDL_Color BgColor, SDL_Color FillColor){
        bgBar.x = origin.x;
        bgBar.y = origin.y;
        valueBar.x = origin.x;
        valueBar.y = origin.y;
        bgBar.h = height;
        bgBar.w = width;
        valueBar.w = width; 

        bgColor = BgColor;
        fillColor = FillColor;
    }

    void RenderBar(SDL_Renderer* renderer, float percentageFull){
        valueBar.w = percentageFull * bgBar.w;
        std::cout << valueBar.w << "\n";
        SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderFillRect(renderer, &valueBar);

        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &bgBar);

        
    }
};
