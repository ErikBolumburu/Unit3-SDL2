#pragma once
#include <Vector2.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL.h>

class Tile{
    public:
        Vector2 position;
        float temperature;
        SDL_Texture* texture;
        SDL_Rect rect;

        Tile(){};
        Tile(Vector2 Position, float Temperature){
            position = Position;
            rect.x = position.x * 80;
            rect.y = position.y * 80;
            rect.w = 80;
            rect.h = 80;
            temperature = Temperature;
        }

        void UpdateTilePosition(Vector2 playerPos){
            rect.x = (position.x * 80) + -playerPos.x;
            rect.y = (position.y * 80) + -playerPos.y;
        }
};
