#pragma once
#include <Tile.hpp>
#include <Vector2.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <RenderWindow.hpp>
#include <iostream>
#include <FastNoiseLite.h>
#include <Bush.hpp>
#define WIDTH 100
#define HEIGHT 100
#define SAND_THRESHOLD 0.25
#define GRASS_THRESHOLD -0.25

class World{
    public:
        int seed;
        Tile tiles[WIDTH][HEIGHT];
        std::vector<Bush> bushes;
        FastNoiseLite noise;

        void GenerateWorld(){
            srand((unsigned int)time(NULL)); // Generate A Random Number To Use For The Seed
            int seed = std::rand();
            noise = FastNoiseLite(seed);
            noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
            noise.SetFrequency(0.01f);
            noise.SetFractalLacunarity(2);
            noise.SetFractalGain(0.5f);

            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    float temperature = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
                    TileType type;
                    if(temperature > SAND_THRESHOLD){
                        type = TileType::SAND;
                    }
                    else if(temperature < SAND_THRESHOLD && temperature > GRASS_THRESHOLD){
                        type = TileType::GRASS;
                    }
                    else if(temperature < GRASS_THRESHOLD){
                        type = TileType::SNOW;
                    }
                    tiles[x][y] = Tile(Vector2(x, y), temperature, type);
                }
            }

            GenerateFood();

        }

        void GenerateFood(){
            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    if(tiles[x][y].type == TileType::GRASS){
                        if((std::rand() % 10) == 0){ // 10% Chance (0-9)
                            Bush bush(&tiles[x][y].rect, Vector2(x, y));
                            bushes.push_back(bush);
                        }
                    }
                }
            }            
        }

        int DistanceBetween(Vector2 a, Vector2 b){
            return abs((a.x - b.x) + (a.y - b.y));
        }

        void RenderWorld(RenderWindow renderWindow, Vector2 playerPos, SDL_Texture* grassTexture, SDL_Texture* sandTexture, SDL_Texture* snowTexture, SDL_Texture* bushTex, SDL_Texture* berryTex){
            for(int x = 0; x < WIDTH; x++){
                for(int y = 0; y < HEIGHT; y++){
                    tiles[x][y].UpdateTilePosition(playerPos);
                    if(tiles[x][y].type == TileType::SAND){
                       SDL_RenderCopy(renderWindow.renderer,
                           sandTexture,
                           NULL, &tiles[x][y].rect);
                   }
                   else if(tiles[x][y].type == TileType::GRASS){
                       SDL_RenderCopy(renderWindow.renderer,
                           grassTexture,
                           NULL, &tiles[x][y].rect);
                   }
                   else if(tiles[x][y].type == TileType::SNOW){
                       SDL_RenderCopy(renderWindow.renderer,
                           snowTexture,
                           NULL, &tiles[x][y].rect);
                   }
                }
            }

            for(Bush bush : bushes){
                bush.Draw(renderWindow.renderer, bushTex, berryTex);
            }

        }
};
