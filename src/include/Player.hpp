#pragma once

#include <GameObject.hpp>
#include <SDL2/SDL.h>
#include <Transform.hpp>
#include <iostream>
#include <vector>

class Player : public GameObject{ // Create a new class called Player that derives from the abstract class 'GameObject'
    public: // All variables and functions in this section are accessible outside of the script
        Player(){}; // Do nothing but create the object if no arguements are passed through
        float moveSpeed = 200; // Set the moveSpeed of the player to 200
        Player(Transform trans){ // If a transform is provided, make the players transform the same and use that to make sure the SDL_Rect is in the correct place and is the correct scale
            transform = trans;
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }
        virtual void Update() override {
            // Every frame, ensure that the players SDL_Rect is in the correct place and is the correct scale in order to avoid the program thinking a player should be rendered somewhere other than where it is
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;

            transform.Move(transform.velocity); // Every frame, move the player depending on its transform.velocity
        }
        void PlayerInput(SDL_Event event){ // Handle all player input and generate the expected output
            // If the program detects a key has been pushed down
            //      Check what key is pressed
            //          If the key is an accepted player input do xyz
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
            // If the program detects a key has been pushed down
            //      Check what key is pressed
            //          If the key is an accepted player input do xyz
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