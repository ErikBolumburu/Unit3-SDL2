#pragma once // Only copy this file into each requested file once to avoid duplicate text
#include <GameObject.hpp> 
#include <vector>

class Wall : public GameObject{ // Create a new class called Wall that derives from the abstract class 'GameObject'
    public: // All variables and functions in this section are accessible outside of the script
        Wall(){}; // Do nothing but create the object if no arguements are passed through
        Wall(Transform trans){ // If a transform is provided, make the walls transform the same and use that to make sure the SDL_Rect is in the correct place and is the correct scale
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
        }
};