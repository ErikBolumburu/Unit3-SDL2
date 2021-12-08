#pragma once
#include <GameObject.hpp>
#include <SDL2/SDL.h>
#include <Transform.hpp>
#include <iostream>
#include <vector>
#include <Game.hpp>
#include <Hunger.hpp>

class Player : public GameObject{
    public:
        Player(){};

        Hunger hunger;

        float moveSpeed = 1;
        Player(Transform trans, int w, int h){
            transform = trans;
            rect.x = (w / 2) - (transform.scale.x / 2);
            rect.y = (h / 2) - (transform.scale.y / 2);
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }

        virtual void Update() override {
            // rect.x = transform.position.x;
            // rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
            transform.position = transform.position + transform.velocity;
            hunger.DecreaseHunger(1);
        }           

        void Movement(SDL_Event event){
            if(event.type == SDL_KEYDOWN){ 
                if(event.key.keysym.scancode == SDL_SCANCODE_W){
                    transform.velocity.y = -moveSpeed; // Move up
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_A){
                    transform.velocity.x = -moveSpeed; // Move Left
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_S){
                    transform.velocity.y = moveSpeed; // Move Down
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_D){
                    transform.velocity.x = moveSpeed; // Move Right
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
