#pragma once
#include <Tile.hpp>
#include <GameObject.hpp>

struct Bush : public GameObject{
    bool hasBerries = true;
    SDL_Rect* tileRect;
    Vector2 pos;

    Bush(SDL_Rect* TileRect, Vector2 Position){
        tileRect = TileRect;
        pos = Position;
    }

    void Draw(SDL_Renderer* renderer, SDL_Texture* bushTex, SDL_Texture* berryTex){
        SDL_RenderCopy(renderer, bushTex, NULL, tileRect);
        if(hasBerries == true){
            SDL_RenderCopy(renderer, berryTex, NULL, tileRect);
        }
    }

    virtual void Update() override {}

};