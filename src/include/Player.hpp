#pragma once
#include <GameObject.hpp>
#include <SDL2/SDL.h>
#include <Transform.hpp>
#include <iostream>
#include <vector>
#include <Game.hpp>
#include <Hunger.hpp>
#include <Health.hpp>
#include <Temperature.hpp>
#include <Tile.hpp>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

class Player : public GameObject{
    public:
        Player(){};

        Hunger hunger;
        Health health;
        Temperature temperature;

        Tile currentTile;

        const float baseMoveSpeed =  0.5f;
        const float wellFedMoveSpeed = baseMoveSpeed * hunger.wellFedMoveSpeedMultiplier;
        float moveSpeed = baseMoveSpeed;

        Player(Transform trans){
            transform = trans;
            rect.x = (SCREENWIDTH / 2) - (transform.scale.x / 2);
            rect.y = (SCREENHEIGHT / 2) - (transform.scale.y / 2);
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }

        virtual void Update() override {
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;

            transform.position = transform.position + transform.velocity;

            MinusHunger();
            IsStarving();
            IsWellFed();
            IsHotOrCold();
        }           

        void MinusHunger(){
            if(transform.velocity.x != 0 || transform.velocity.y != 0){ // Lose hunger faster if moving
                hunger.DecreaseHunger(0.002f);
            }
            else{
                hunger.DecreaseHunger(0.0015f);
            }
        }

        void IsStarving(){
            if(hunger.value <= hunger.starveThreshold){
                health.LowerHealth(0.01f);
            }
        }

        void IsWellFed(){
            if(hunger.value >= hunger.wellFedThreshold){
                moveSpeed = wellFedMoveSpeed;
            }
            else{
                moveSpeed = baseMoveSpeed;
            }
        }

        void IsHotOrCold(){
            temperature.ApplyStatus();
            if(temperature.hypothermia || temperature.hyperthermia){
                health.LowerHealth(0.01f);
            }
        }

        // FIXME: Players Transform Is In Pixels/Floating Point/IDK Some Decimal Where As Tiles Are In Grid Space. This cause bad. Figure Soon Out Please.
        void SetCurrentTile(World world){
            currentTile = world.tiles[static_cast<int>(transform.position.x) / 80][static_cast<int>(transform.position.y) / 80];
            std::cout << "X = " << currentTile.position.x << ", Y = " << currentTile.position.y << "\n";
            //std::cout << transform.position.x << "\n";
        };

        void Movement(SDL_Event event, float dT){
            if(event.type == SDL_KEYDOWN){ 
                if(event.key.keysym.scancode == SDL_SCANCODE_W){
                    transform.velocity.y = -moveSpeed * dT; // Move up
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_A){
                    transform.velocity.x = -moveSpeed * dT; // Move Left
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_S){
                    transform.velocity.y = moveSpeed * dT; // Move Down
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_D){
                    transform.velocity.x = moveSpeed * dT; // Move Right
                }
            }
            else if(event.type == SDL_KEYUP){
                if(event.key.keysym.scancode == SDL_SCANCODE_W){
                    transform.velocity.y = 0;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_A){
                    transform.velocity.x = 0;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_S){
                    transform.velocity.y = 0;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_D){
                    transform.velocity.x = 0;
                }
        }
    }
};
