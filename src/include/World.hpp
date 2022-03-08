#pragma once
#include <Tile.hpp>
#include <Vector2.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <RenderWindow.hpp>
#include <iostream>
#include <FastNoiseLite.h>
#define WIDTH 100
#define HEIGHT 100
#define SAND_THRESHOLD 0.25
#define GRASS_THRESHOLD -0.25

class World{
    public:
        int seed;
        Tile tiles[WIDTH][HEIGHT];
        FastNoiseLite noise;

        void GenerateWorld(){
            srand((unsigned int)time(NULL)); // Generate A Random Number To Use For The Seed
            int seed = std::rand();
            noise = FastNoiseLite(seed);
            noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
            noise.SetFrequency(0.001f);
            noise.SetFractalOctaves(3);
            noise.SetFractalLacunarity(2);
            noise.SetFractalGain(0.5f);

            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    float temperature = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
                    if(tiles[x][y].temperature > SAND_THRESHOLD){
                        tiles[x][y].type = 0;
                    }
                    else if(tiles[x][y].temperature < SAND_THRESHOLD && tiles[x][y].temperature > GRASS_THRESHOLD){
                        tiles[x][y].type = 1;
                    }
                    else if(tiles[x][y].temperature < GRASS_THRESHOLD){
                        tiles[x][y].type = 2;
                    }
                    tiles[x][y] = Tile(Vector2(x, y), temperature);
                }
            }
        }

        void RenderWorld(RenderWindow renderWindow, Vector2 playerPos, SDL_Texture* grassTexture, SDL_Texture* sandTexture, SDL_Texture* snowTexture){
            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    tiles[x][y].UpdateTilePosition(playerPos);
                    if(tiles[x][y].type == 0){
                       SDL_RenderCopy(renderWindow.renderer,
                           sandTexture,
                           NULL, &tiles[x][y].rect);
                   }
                   else if(tiles[x][y].type == 1){
                       SDL_RenderCopy(renderWindow.renderer,
                           grassTexture,
                           NULL, &tiles[x][y].rect);
                   }
                   else if(tiles[x][y].type == 2){
                       SDL_RenderCopy(renderWindow.renderer,
                           snowTexture,
                           NULL, &tiles[x][y].rect);
                   }
                }
            }
        }
};
