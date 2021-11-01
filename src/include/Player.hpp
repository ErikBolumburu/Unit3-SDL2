#pragma once

#include <GameObject.hpp>
#include <SDL2/SDL.h>
#include <Transform.hpp>
#include <iostream>
#include <vector>

class Player : public GameObject{
    public:
        Player(){
        };
        float moveSpeed = 200;
        bool grounded = false;
        Player(Transform trans){
            transform = trans;
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }
        virtual void Update() override {
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;

            transform.Move(transform.velocity);
        }
        void PlayerInput(SDL_Event event){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.scancode == SDL_SCANCODE_W){
                    transform.velocity.y = -moveSpeed;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_A){
                    transform.velocity.x = -moveSpeed;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_S){
                    transform.velocity.y = moveSpeed;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_D){
                    transform.velocity.x = moveSpeed;
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