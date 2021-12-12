#pragma once
#include <GameObject.hpp>
#include <SDL2/SDL.h>
#include <Transform.hpp>
#include <iostream>
#include <vector>
#include <Game.hpp>
#include <Hunger.hpp>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

class Player : public GameObject{
    public:
        Player(){};

        Hunger hunger;

        float moveSpeed = 0.5f;
        Player(Transform trans){
            transform = trans;
            rect.x = (SCREENWIDTH / 2) - (transform.scale.x / 2);
            rect.y = (SCREENHEIGHT / 2) - (transform.scale.y / 2);
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }

        virtual void Update() override {
            // rect.x = transform.position.x;
            // rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
            transform.position = transform.position + transform.velocity;
            //hunger.DecreaseHunger(1);
        }           

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
